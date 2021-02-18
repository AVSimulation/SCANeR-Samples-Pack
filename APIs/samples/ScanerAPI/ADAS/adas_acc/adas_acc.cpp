/*!**************************************************************************************************************
* \project  : SCANeR_API																						*
* \file     : adas_lka.cpp																						*
* \Brief    : Description: Control streering lateral commands to follow road markings.							*
*****************************************************************************************************************/
//C/C++ includes
#include <iostream>

//scaner project includes
#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesShm.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"
#include "stk/Vector3.h"
#include "stk/Unit.h"

#define PI 3.1415926535897932384626

int main(int argc, char* argv[])
{
	Process_Init(argc, argv); // get configuration and module name

	int egoID = 0;
	int egoRadarGlobalID = 300000;

	//PREPARE access to the SCANeR data

	DataInterface* egoState = Com_declareInputData(NETWORK_IVEHICLE_VEHICLEUPDATE, egoID); // vehicle status update
	DataInterface* egoCustomInputs = Com_declareInputData(NETWORK_IVEHICLE_CUSTOMVEHICLEINPUT, egoID); //  vehicle custom inputs from the human driver and control pad
	DataInterface* egoRadarData = Com_declareInputData(NETWORK_ISENSOR_SENSORMOVABLETARGETS, egoRadarGlobalID); // radar sensor outputs
	DataInterface* exportChannel = Com_declareInputData(NETWORK_IUSER_EXPORTCHANNEL, 66);

	DataInterface* longitudinalControl = Com_declareOutputData(SHM_MODELCABIN_CABTOMODELCORRECTIVE, egoID); // includes pedal commands
	DataInterface* egoOverrideCustomInput = Com_declareOutputData(NETWORK_IVEHICLE_OVERRIDECUSTOMVEHICLEINPUT, egoID); // vehicle custom outputs 

	float ACC_mode = 0.f, ACC_mode_old = 0.f;

	APIProcessState status = PS_DAEMON;

	while (status != PS_DEAD) // main loop
	{
		double TimeOfUpdate_old = Process_GetTime();

		Process_Wait(); // syncrhonization
		Process_Run(); // step + state update (optional: if the register event method is used then the message will be queud calling this method).
		status = Process_GetState();

		double TimeOfUpdate = Process_GetTime();

		if (status == PS_RUNNING) // simulation is running
		{
			if (!Com_updateInputs(UT_AllData))
			{
				Process_OutputLevel("ERROR: Cannot read SCANeR messages", OL_Err);
			}
			else
			{
				// READ custom input 2 : ACC mode
				ACC_mode_old = ACC_mode;
				ACC_mode = Com_getFloatData(egoCustomInputs, "customInputValues[2]");
				if (ACC_mode > 0.f)
				{
					static double _positionError_old = 0.;
					static double _positionError_i = 0.;
					static double _speedError_old = 0.;
					static double _speedError_i = 0.;

					if (ACC_mode != ACC_mode_old)
					{
						//reset PIDs
						_positionError_old = 0.;
						_positionError_i = 0.;
						_speedError_old = 0.;
						_speedError_i = 0.;
					}

					// READ the simulation data from SCANeR
					float egoSpeed_mps = Com_getFloatData(egoState, "speed[0]"); //actual longitudinal speed in the SCANeR vehicle state
					float egoSpeed_kmph = egoSpeed_mps * 3600.f / 1000.f;
						
					short detectedVehiclesCount = Com_getShortData(egoRadarData, "targetsArrayCount"); //amount of vehicles detected by the SCANeR radar sensor
					float distanceToCollision = 0.f, followSpeed_kmph = 0.f;
					if (detectedVehiclesCount > 0)
					{
						distanceToCollision = Com_getFloatData(egoRadarData, "targetsArray[0]/distanceToCollision"); //distance from the SCANeR radar sensor
						float followSpeed_mps = Com_getFloatData(egoRadarData, "targetsArray[0]/absoluteSpeedX");
						followSpeed_kmph = followSpeed_mps * 3600.f / 1000.f;
					}

					float requiredSpeed = Com_getFloatData(exportChannel, "val");

					// COMPUTE the command
					double accelerationAdditive = 0., AcceleratorMultiplicative = 1., BrakeAdditive = 0.;

					float requiredDistance = 0.f;
					if (ACC_mode == 1.0)
						requiredDistance = 20.f;
					else if (ACC_mode == 2.0)
						requiredDistance = 30.f;
					else if (ACC_mode == 3.0)
						requiredDistance = 40.f;
					else if (ACC_mode == 4.0)
						requiredDistance = 50.f;
					else
						Process_OutputLevel("ERROR: Unknown ACC distance", OL_Err);

					// Position PID - output : target speed

					double targetSpeed = 0.;

					if (detectedVehiclesCount > 0) // enought point to find a point to follow
					{
						double positionError = distanceToCollision - requiredDistance;
						double positionError_d = (positionError - _positionError_old) / (TimeOfUpdate - TimeOfUpdate_old);
						_positionError_i += positionError * (TimeOfUpdate - TimeOfUpdate_old);
						if (_positionError_i > 1.) _positionError_i = 1.;
						
						targetSpeed = .5*positionError + .5*positionError_d + 1e-4*_positionError_i + followSpeed_kmph;

						if (targetSpeed > requiredSpeed)
						{
							targetSpeed = requiredSpeed;
						}

						_positionError_old = positionError;
					}
					else
					{
						targetSpeed = requiredSpeed;
					}

					// Speed PID - output : commands

					double speedError = targetSpeed - egoSpeed_kmph;
					double speedError_d = (speedError - _speedError_old) / (TimeOfUpdate - TimeOfUpdate_old);
					_speedError_i += speedError * (TimeOfUpdate - TimeOfUpdate_old);

					double command = .1*speedError + .1*speedError_d + 5e-4*_speedError_i;

					if (command > 0.)
					{
						accelerationAdditive = command*1.;
						AcceleratorMultiplicative = 1.;
						BrakeAdditive = 0.;
					}
					else
					{
						accelerationAdditive = 0.;
						AcceleratorMultiplicative = 0.;
						BrakeAdditive = -command*20.;
					}

					_speedError_old = speedError;

					//SEND the commands to the SCANeR vehicle
					Com_setDoubleData(longitudinalControl, "AcceleratorAdditive", accelerationAdditive);
					Com_setDoubleData(longitudinalControl, "AcceleratorMultiplicative", AcceleratorMultiplicative);
					Com_setDoubleData(longitudinalControl, "BrakeAdditive", BrakeAdditive);

					Com_setFloatData(egoOverrideCustomInput, "input[0]/value", requiredDistance);
				}
				else
				{
					//ACC is OFF, send no correction
					Com_setDoubleData(longitudinalControl, "AcceleratorAdditive", 0.);
					Com_setDoubleData(longitudinalControl, "AcceleratorMultiplicative", 1.);
					Com_setDoubleData(longitudinalControl, "BrakeAdditive", 0.);

					Com_setFloatData(egoOverrideCustomInput, "input[0]/value", FLT_MAX);
				}
				//send no correction to unused commands
				Com_setDoubleData(longitudinalControl, "BrakeMultiplicative", 1.);
				Com_setDoubleData(longitudinalControl, "ClutchAdditive", 0.);
				Com_setDoubleData(longitudinalControl, "ClutchMultiplicative", 1.);
				Com_setDoubleData(longitudinalControl, "ParkingBrakeAdditive", 0.);
				Com_setDoubleData(longitudinalControl, "ParkingBrakeMultiplicative", 1.);
				Com_setCharData(longitudinalControl, "GearboxTakeOver", 0);
				Com_setDoubleData(longitudinalControl, "TimeOfUpdate", TimeOfUpdate);

				Com_setShortData(egoOverrideCustomInput, "vhlId", 0);
				Com_setShortData(egoOverrideCustomInput, "inputCount", 1);
				Com_setShortData(egoOverrideCustomInput, "input[0]/index", 3);
				Com_setCharData(egoOverrideCustomInput, "input[0]/isOverride", 1);

				//APPLY the modifications (actually send the messages on the SCANeR Network)
				if (!Com_updateOutputs(UT_AllData))
					Process_OutputLevel("ERROR: Cannot write on network or shared memory", OL_Err);
			}
		}
	}
	Process_Close();
	return 0;
}
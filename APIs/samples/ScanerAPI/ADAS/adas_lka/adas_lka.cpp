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
#define LKA_MARGIN .5

int main(int argc, char* argv[])
{
	Process_Init(argc, argv); // get configuration and module name

	Com_registerEvent("START"); // register start event

	double maxWheelsAngle = stk::convToUnit(stk::TUnitDegre, 40.86);
	double maxSteeringWheelAngle = stk::convToUnit(stk::TUnitDegre, 540);

	int vehicleID = 0;
	int roadSensorGlobalID = 100000;
	DataInterface* vehicleInputs = Com_declareInputData(NETWORK_IVEHICLE_CUSTOMVEHICLEINPUT, vehicleID); // prepare access to vehicle custom inputs from the human driver
	DataInterface* roadSensor = Com_declareInputData(NETWORK_ISENSOR_ROADLINESPOINTS, roadSensorGlobalID); // read access to road sensor outputs

	int vhcID = 0;
	DataInterface* lateralControl = Com_declareOutputData(SHM_MODELCABIN_CABTOSTEERINGCORRECTIVE, vhcID); // write access to streering commands

	float LKAState = 0.f;

	APIProcessState status = PS_DAEMON;

	while (status != PS_DEAD) // main loop
	{
		Process_Wait(); // syncrhonization
		Process_Run(); // step + state update (optional: if the register event method is used then the message will be queud calling this method).

		double TimeOfUpdate = Process_GetTime();
		status = Process_GetState();

		Event* event;
		while (event = Com_getNextEvent()) // read recorded events (in this sample START state)
		{
			EventType evtType = Com_getTypeEvent(event);
			if (evtType == ET_state)
			{
				StateEventType evtStateType = Com_getStateEventType(event);
				switch (evtStateType)
				{
				case ST_Start: // get information before that the simulation starts
				{
					VehicleInfoStruct vhcinfo;
					if (!Utils_getVehicleInformations(0, &vhcinfo)) // get access to maxWheelsAngle and maxSteeringWheelAngle (rad)
						Process_OutputLevel("WARNING: Cannot access to vehicle informations. Default values will be used.", OL_Warning);
					else
					{
						maxWheelsAngle = vhcinfo.maxWheelsAngle; // rad
						maxSteeringWheelAngle = vhcinfo.maxSteeringWheelAngle; // rad
					}
					Com_validateStateEvent(event); // Need to validate the state change
					break;
				}
				default:
				{
					Process_OutputLevel("NOTIFY: State not managed.", OL_Notify);
					break;
				}
				}
			}
		}

		if (Process_GetState() == PS_RUNNING) // simulation is running
		{
			if (!Com_updateInputs(UT_NetworkData))
			{
				Process_OutputLevel("ERROR: Cannot read network messages", OL_Err);
			}
			else
			{
				LKAState = Com_getFloatData(vehicleInputs, "customInputValues[0]");
				if (LKAState > 0.f)
				{
					short roadSensorCount = Com_getShortData(roadSensor, "roadLinesPointsArrayCount"); // Number of points into the matrice
					if (roadSensorCount >= 10) // enought point to find a point to follow
					{
						double AdditiveSteeringWheelAngle = 0;
						stk::Vector3 roadSensorPointL, roadSensorPointR;
						// read matrice points from road sensor from the sensor reference system
						roadSensorPointL.x = Com_getDoubleData(roadSensor, "roadLinesPointsArray[4]/pointX");
						roadSensorPointL.y = Com_getDoubleData(roadSensor, "roadLinesPointsArray[4]/pointY");
						roadSensorPointL.z = Com_getDoubleData(roadSensor, "roadLinesPointsArray[4]/pointZ");
						roadSensorPointR.x = Com_getDoubleData(roadSensor, "roadLinesPointsArray[6]/pointX");
						roadSensorPointR.y = Com_getDoubleData(roadSensor, "roadLinesPointsArray[6]/pointY");
						roadSensorPointR.z = Com_getDoubleData(roadSensor, "roadLinesPointsArray[6]/pointZ");

						stk::Vector3 targetedPoint = (roadSensorPointL + roadSensorPointR) / 2.f; // target the middle of the road

						if (fabs(targetedPoint.y) >= LKA_MARGIN) {

							targetedPoint.normalize();
							double targetWheelAngle = atan2(targetedPoint.y, targetedPoint.x); // wheel angle related to the targeted point
							AdditiveSteeringWheelAngle = .02 * (targetWheelAngle / maxWheelsAngle) * maxSteeringWheelAngle; // convert wheel angle to steering angle (rad)

							// apply the computed streering wheel angle
							Com_setDoubleData(lateralControl, "AdditiveSteeringWheelAngle", AdditiveSteeringWheelAngle);
						}
						else {
							Com_setDoubleData(lateralControl, "AdditiveSteeringWheelAngle", 0);
						}

						
					}
					else
						Process_OutputLevel("WARNUNG: Road Marking sensor not configured for this sample (= 2 scans with a space of 5 meters so 4 points in the matrice)", OL_Warning);
				}
				else
				{
					Com_setDoubleData(lateralControl, "AdditiveSteeringWheelAngle", 0);
				}

				Com_setDoubleData(lateralControl, "MultiplicativeSteeringWheelAngle", 1.f);
				Com_setDoubleData(lateralControl, "AdditiveSteeringWheelSpeed", 0);
				Com_setDoubleData(lateralControl, "MultiplicativeSteeringWheelSpeed", 1);
				Com_setDoubleData(lateralControl, "AdditiveSteeringWheelAccel", 0);
				Com_setDoubleData(lateralControl, "MultiplicativeSteeringWheelAccel", 1);
				Com_setDoubleData(lateralControl, "AdditiveSteeringWheelTorque", 0);
				Com_setDoubleData(lateralControl, "MultiplicativeSteeringWheelTorque", 1);
				Com_setDoubleData(lateralControl, "TimeOfUpdate", TimeOfUpdate);

				if (!Com_updateOutputs(UT_ShmData))
					Process_OutputLevel("ERROR: Cannot write on shared memory (= this module must be executed on same computer as ACQUISITION and MODELHANDLER)", OL_Err);

				if (!Com_updateOutputs(UT_NetworkData))
					Process_OutputLevel("ERROR: Cannot write on network", OL_Err);
			}
		}
	}
	Process_Close();
	return 0;
}
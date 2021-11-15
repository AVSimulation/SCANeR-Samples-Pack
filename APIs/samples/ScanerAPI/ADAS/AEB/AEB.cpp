#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesShm.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	/* Initialization of the scaner api module into the scaner configuration */
	if (Process_Init(argc, argv) == -1) // init the scaner api module into the scaner configuration
	{
		std::cout << "Error while initializing SCANeR API. Exiting" << std::endl;
		return 1;
	}

	APIProcessState status = PS_DAEMON; // init scaner api module to Process State DAEMON

	/* Input */
	DataInterface* vhc0 = Com_declareInputData(NETWORK_IVEHICLE_VEHICLEUPDATE, 0); // read access to EGO vehicle outputs
	DataInterface* radar_300000 = Com_declareInputData(NETWORK_ISENSOR_SENSORMOVABLETARGETS, 300000);


	// write access to Shared Memory for longitudinal control
	DataInterface* CabToModelCorrective_0 = Com_declareOutputData(SHM_MODELCABIN_CABTOMODELCORRECTIVE, 0);

	float distanceToCollision = -1;
	float distanceMaxCollision = 20;
	while (status != PS_DEAD)
	{
		Process_Wait(); // scaner api synchronization
		Process_Run(); // scaner api step and update the status of the module
		double TimeOfUpdate = Process_GetTime();

		status = Process_GetState(); // this method return the current module state

		if (status == PS_RUNNING) // when the simulation is running
		{
			Com_updateInputs(UT_NetworkData); // update scaner network messages to read (Com_declareInputData)

			short targetsCount = Com_getShortData(radar_300000, "targetsArrayCount");
			if (targetsCount > 0)
			{
				char distanceToCollisionTmp[50];
				sprintf_s(distanceToCollisionTmp, "targetsArray[%d]/distanceToCollision", Com_getShortData(radar_300000, "nearestTarget"));
				distanceToCollision = Com_getFloatData(radar_300000, distanceToCollisionTmp);
			}

			Process_OutputLevel(std::to_string(distanceToCollision).c_str(), OL_Notify);

			if (distanceToCollision != -1)
			{
				if (distanceToCollision < distanceMaxCollision) // export channel value used to definr the distanceToCollision
				{
					// add brake assistance
					Com_setDoubleData(CabToModelCorrective_0, "BrakeAdditive", 400);
					Com_setDoubleData(CabToModelCorrective_0, "BrakeMultiplicative", 0);
					Com_setDoubleData(CabToModelCorrective_0, "AccelMultiplicative", 0);
					Com_setDoubleData(CabToModelCorrective_0, "TimeOfUpdate", TimeOfUpdate);
					if (!Com_updateOutputs(UT_ShmData)) // flush the corrective message
						std::cout << "Update Shm outputs failed..." << std::endl;
				}
				distanceToCollision = -1;
			}
		}
	}
	Process_Close();
	return 0;
}
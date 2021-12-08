/*!****************************************************************************
 * \project  : SCANeR_API                                                     *
 * \file     : EVAL_LONGITUDINAL_CTRL_PEDALPOS.cpp                 			  *
 * \Brief    : Radar sensor, targets detection with SCANeR API.	              *
 * \Copyright: OKTAL S.A. all rights reserved                                 *
 ******************************************************************************/
//C/C++ includes
#include <iostream>
#include <map>
#include <string>

//scaner project includes
#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"
#include "scanerAPI/ScanerAPImessagesShm.h"

int main(int argc, char* argv[])
{
	Process_Init(argc, argv);
	APIProcessState status = PS_DAEMON;

	// read access to radar and ExportChannel
	DataInterface* radar_300000				= Com_declareInputData(NETWORK_ISENSOR_SENSORMOVABLETARGETS, 300000);
	DataInterface* EC_1000					= Com_declareInputData(NETWORK_IUSER_EXPORTCHANNEL, 67);
	// write access to Shared Memory for longitudinal control
	DataInterface* CabToModelCorrective_0	= Com_declareOutputData(SHM_MODELCABIN_CABTOMODELCORRECTIVE, 0);

	float distanceToCollision = -1;

	while (status != PS_DEAD) // main loop
	{
		Process_Wait(); // syncrhonization
		Process_Run(); // step

		double TimeOfUpdate = Process_GetTime();

		status = Process_GetState();

		if (status == PS_RUNNING) // simulation is running
		{
			if (!Com_updateInputs(UT_NetworkData)) // get last network message
				std::cout << "Update Network inputs failed..." << std::endl;

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
				if (distanceToCollision < Com_getFloatData(EC_1000, "val")) // export channel value used to definr the distanceToCollision
				{
					// add brake assistance
					Com_setDoubleData(CabToModelCorrective_0, "BrakeAdditive", 400);
					Com_setDoubleData(CabToModelCorrective_0, "BrakeMultiplicative", 0);
					Com_setDoubleData(CabToModelCorrective_0, "TimeOfUpdate", TimeOfUpdate);
					if (!Com_updateOutputs(UT_ShmData)) // flush the corrective message
						std::cout << "Update Shm outputs failed..." << std::endl;
				}
				distanceToCollision = -1;
			}
		}
	} // EoWhile(1)
	Process_Close();
}
//--------------------------------------------------------------
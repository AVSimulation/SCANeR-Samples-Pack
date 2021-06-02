/*! includes **/
#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"
#include "NightTest/NightTest.h"
#include "NightTest/Product.h"
#include "NightTest/OpticalFunction.h"
#include "NightTest/Projector.h"
#include "NightTest/LightSource.h"
#include "NightTest/Location.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

bool ChangeOrientation(const char* inputNightTest, double newHeading)
{
	bool res = false;
	NT_NightTest* nt = NT_CreateNightTest("NightTestAPI_LoadingSample");
	if (nt)
	{
		if (NT_NightTestLoad(nt, inputNightTest))
		{
			double x = 0.0, y = 0.0, z = 0.0;
			double heading = 0.0, aiming = 0.0, roll = 0.0;

			unsigned int productsNb = NT_NightTestGetProductsNumber(nt);

			for (unsigned int prodId = 0; prodId < productsNb; prodId++)
			{
				NT_Product* currProd = NT_NightTestGetProductAt(nt, prodId);
				if (!currProd)
					continue;

				unsigned int ofNb = NT_ProductGetOpticalFunctionsNumber(currProd);
				//Go through each optical function
				for (unsigned int ofId = 0; ofId < ofNb; ofId++)
				{
					NT_OpticalFunction* currOF = NT_ProductGetOpticalFunctionAt(currProd, ofId);
					if (!currOF)
						continue;

					unsigned int prjNb = NT_OpticalFunctionGetProjectorsNumber(currOF);
					for (unsigned int prjId = 0; prjId < prjNb; prjId++)
					{
						NT_Projector* currPRJ = NT_OpticalFunctionGetProjectorAt(currOF, prjId);
						if (!currPRJ)
							continue;

						//Read lightsources parameters and print 
						while (NT_ProjectorGetLightSourcesNumber(currPRJ) > 0)
						{
							NT_LightSource* currLS = NT_ProjectorGetLightSourceAt(currPRJ, 0);
							if (!currLS)
								continue;
							//CURRENT 
							NT_LightSourceGetPosition(currLS, &x, &y, &z, &heading, &aiming, &roll);
							//printf("      + LIGHT : %s\n", NT_LightSourceGetName(currLS));
							//printf("        - photometry : %s\n", NT_LightSourceGetPhotometryName(currLS));
							//printf("        - AFS strategy : %s\n", NT_LightSourceGetAFSStrategy(currLS));
							//printf("        - x : %f\n", x);
							//printf("        - y : %f\n", y);
							//printf("        - z : %f\n", z);
							//printf("        - heading : %f\n", heading);
							//printf("        - aiming : %f\n", aiming);
							//printf("        - roll : %f\n", roll);

							//X POSITION MODIFICATION
							NT_LightSourceSetPosition(currLS, x, y, z, newHeading, aiming, roll);
							NT_LightSourceGetPosition(currLS, &x, &y, &z, &heading, &aiming, &roll);


							//New heading
							printf("        - new heading : %f\n", heading);

							if (NT_NightTestSave(nt, inputNightTest, 0))
							{
								printf("NightTest file saved in '%s'.\n", inputNightTest);
							}
							//Delete
							NT_ProjectorRemoveLightSource(currPRJ, currLS);
							NT_DeleteLightSource(currLS);
							printf("        - Light Source Deleted.\n");
							res = true;
						}
					}
				}
			}
		}
		else
		{
			printf("Could not load Night test \n");
		}
	}
	NT_DeleteNightTest(nt);
	return res;
}

void TakeSnapShot(DataInterface* SnapshotInterfaceOutput, long SnapshotType, const char* path)
{
	Com_setLongData(SnapshotInterfaceOutput, "type", SnapshotType);
	Com_setStringData(SnapshotInterfaceOutput, "path", path);
	Com_setStringData(SnapshotInterfaceOutput, "channelName", "");
	Com_setStringData(SnapshotInterfaceOutput, "recordPathSuffix", "hl");
}
void SendSensorsListInformation(DataInterface* SensorListOutput, short sensorCount, long sensorId, float sensorPosition[3], float sensorNorm[3], long referenceCarId, char isVisible, char isActivated, char sensorRGB[3])
{
	Com_setShortData(SensorListOutput, "SensorCount", sensorCount);
	Com_setLongData(SensorListOutput, "Sensor[0]/Id", sensorId);
	Com_setFloatData(SensorListOutput, "Sensor[0]/x", sensorPosition[0]);
	Com_setFloatData(SensorListOutput, "Sensor[0]/y", sensorPosition[1]);
	Com_setFloatData(SensorListOutput, "Sensor[0]/z", sensorPosition[2]);
	Com_setFloatData(SensorListOutput, "Sensor[0]/normX", sensorNorm[0]);
	Com_setFloatData(SensorListOutput, "Sensor[0]/normY", sensorNorm[1]);
	Com_setFloatData(SensorListOutput, "Sensor[0]/normZ", sensorNorm[2]);
	Com_setLongData(SensorListOutput, "Sensor[0]/ReferenceCarId", referenceCarId);
	Com_setCharData(SensorListOutput, "Sensor[0]/IsVisible", isVisible);
	Com_setCharData(SensorListOutput, "Sensor[0]/IsActivated", isActivated);
	Com_setCharData(SensorListOutput, "Sensor[0]/ColorRed", sensorRGB[0]);
	Com_setCharData(SensorListOutput, "Sensor[0]/ColorGreen", sensorRGB[1]);
	Com_setCharData(SensorListOutput, "Sensor[0]/ColorBlue", sensorRGB[2]);
}
int main(int argc, char* argv[])
{
	/*! Process Com intialization **/
	if (Process_Init(argc, argv) == -1)
	{
		std::cout << "Error while initializing SCANeR API. Exiting" << std::endl;
		return 1;
	}
	/*Read export channels */
	DataInterface* ECInterface = Com_declareInputData(NETWORK_IUSER_EXPORTCHANNEL);
	short EC_ID = 67;//EC ID for Lamp_heading
	/* Load NT File */
	DataInterface* NightTestOutput = Com_declareOutputData(NETWORK_INIGHTTEST_LOADSNTFILE);
	const char* inputNightTest = "D:\\AVSimulation\\SCANeRstudio_2021\\data\\Sample_2021_HL_HPC\\headlights\\nightTest\\Generic_Custom_1.nt"; //The absolute path NT to load
	const char* inputNightTest2 = "Generic_Custom_1.nt"; //The NT to load
	float LAMP_HEADING = 0;
	bool isFirstFrame = true;
	bool ntLoad = true;

	/* Virtual sensors */
	DataInterface* SensorListOutput = Com_declareOutputData(NETWORK_ILIGHTSIMULATION_SENSORLIST);
	DataInterface* SensorUpdate = Com_declareOutputData(NETWORK_ILIGHTSIMULATION_UPDATESENSOR);
	DataInterface* SensorValueInput = Com_declareInputData(NETWORK_ILIGHTSIMULATION_SENSORVALUES);
	/*Parameters*/
	short sensorCount = 1;
	long sensorId = 0;
	float sensorPosition[3] = { 1.3f,0.38f,1.26f };
	float sensorNorm[3] = { 1,0,0 };
	long referenceCarId = 1;
	char isVisible = 1;
	char isActivated = 1;
	char sensorRGB[3] = { 0,-1,-1 };
	float DeBoerValue = -1;

	/* Snapshot */
	DataInterface* SnapshotInterfaceOutput = Com_declareOutputData(NETWORK_IINFORMATION_SENDVISUALSNAPSHOT);
	const char* snapshotFolder = "D:\\AVSimulation\\SCANeRstudio_2021\\data\\Sample_2021_HL_HPC\\snapshots";
	bool picture = true;

	APIProcessState status = PS_DAEMON;
	while (status != PS_DEAD)
	{
		/*! Process manager Run **/
		Process_Wait();
		Process_Run();

		/*! Process manager State **/
		APIProcessState oldStatus = status;
		status = Process_GetState();

		if (oldStatus != status)
		{
			switch (status)
			{
			case PS_DAEMON:
				std::cout << " SCANER API STATUS : DAEMON " << std::endl;
				break;
			case PS_DEAD:
				std::cout << " SCANER API STATUS : DEAD " << std::endl;
				break;
			case PS_LOADED:
				ntLoad = true;
				isFirstFrame = true;
				picture = true;
				DeBoerValue = -1;
				std::cout << " SCANER API STATUS : LOADED " << std::endl;
				break;
			case PS_PAUSED:
				std::cout << " SCANER API STATUS : PAUSED " << std::endl;
				break;
			case PS_READY:
				std::cout << " SCANER API STATUS : READY " << std::endl;
				break;
			case PS_RUNNING:
				std::cout << " SCANER API STATUS : RUNNING " << std::endl;
				break;
			default:
				break;
			}
		}

		/*! Scaner API is now running **/
		if (status == PS_RUNNING)
		{
			/*! get a copy of the structure of exchange data **/
			Com_updateInputs(UT_NetworkData);


			/************** CHANGE NT FILE ******************/
			if (!isFirstFrame)
			{
				//Read EC Value and load
				if (ntLoad)
				{
					if (Com_getShortData(ECInterface, "no") == EC_ID)
					{
						/* Step 1 - Read the new heading value from EC */
						LAMP_HEADING = Com_getFloatData(ECInterface, "val");
						/* Step 2 - Read and modify the .nt file */
						if (ChangeOrientation(inputNightTest, LAMP_HEADING))
						{
							/* Step 3 - Reload the .nt file*/
							Com_setStringData(NightTestOutput, "fileName", inputNightTest2);
							ntLoad = false;
						}
					}
				}
			}
			if (isFirstFrame)
				isFirstFrame = false;
			SendSensorsListInformation(SensorListOutput, sensorCount, sensorId, sensorPosition, sensorNorm, referenceCarId, isVisible, isActivated, sensorRGB);

			
			/********** SNAPSHOT AT 5 SECONDS *************/
			//if (Process_GetTime() > 5 && picture)
			//{
			//	TakeSnapShot(SnapshotInterfaceOutput, 1, snapshotFolder);//type 1 = Luminance
			//	picture = false;
			//}
			/*! put the modified copy in the structure of exchange data **/
			Com_updateOutputs(UT_NetworkData);
			Com_updateInputs(UT_NetworkData);
			DeBoerValue = Com_getFloatData(SensorValueInput, "SensorValue[0]/DeBoerScale");
			if (DeBoerValue != -1)
			{
				printf("Deboer Value : %f \n", DeBoerValue);
			}
		}
		/*! end of loop **/
		if (kbhit() != 0)
			break;
	}
	return 0;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include "SensorsViewer.h"
#include "SensorViewerPixelLightingConfig.h"

#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"

#include <iostream>

//=============================================================================


int main(int argc, char *argv[])
{
	std::cout << "****************************************************************************" << std::endl;
	std::cout << "                   SCANER API DETECT RADAR SENSOR TARGETS                   " << std::endl;
	std::cout << "****************************************************************************" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	//process Com intialization
	if (Process_Init(argc, argv) == -1)
	{
		std::cout << "Error while initializing SCANeR API. Exiting" << std::endl;
		return 1;
	}

	//get the process name
	std::string configName = "DEFAULT";
	std::string procName = "SENSORS_VIEWER";
	for (int i = 1; i < argc; i++)
	{
		std::string currentArg(argv[i]);
		if ((currentArg == "-c") && (i + 1 < argc))
			configName = argv[i + 1];
		else if ((currentArg == "-p") && (i + 1 < argc))
			procName = argv[i + 1];
	}

	//load the configuration file
	SensorViewerPixelLightingConfig config;
	if (!config.load("SensorViewerPixelLighting.cfg", procName))
	{
		Process_Close();
		return 1;
	}

	//register to SCANeR messages
	Com_registerEvent(NETWORK_ISENSOR_SENSORMOVABLETARGETSTRAFFICSTATES);
	Com_registerEvent(NETWORK_ISENSOR_SENSORMOVABLETARGETSBOUNDINGBOXES);
	Com_registerEvent(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETS);
	Com_registerEvent(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETSTRAFFICSTATES);
	Com_registerEvent(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETSBOUNDINGBOXES);
	Com_registerEvent(NETWORK_ILIGHTSIMULATION_HEADLAMPPARAMETERS);

	//viewer
	SensorsViewer viewer(procName, config.myImageWidth, config.myImageHeight);

	APIProcessState status = PS_DAEMON;
	while (status != PS_DEAD)
	{
		//Process manager run
		Process_Wait();
		Process_Run();

		//Process manager State
		APIProcessState oldStatus = status;
		status = Process_GetState();

		//State changing
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
				std::cout << " SCANER API STATUS : LOADED " << std::endl;
				if (oldStatus == PS_DAEMON)
				{
					//get the headlight vehicle info (vehicle 0)
					VehicleInfoStruct vehinfo;
					Utils_getVehicleInformations(0, &vehinfo);
					viewer.setVehicleEyePosition(
						stk::Vector3(vehinfo.eyePosition.x, vehinfo.eyePosition.y, vehinfo.eyePosition.z));

					//start the viewer
					viewer.load();
				}
				if (oldStatus == PS_RUNNING)
				{
					//stop the viewer
					viewer.clear();
				}
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

		//Run process
		if (status == PS_RUNNING)
		{
			std::map <short, bool> pedestrianCrossings;
			std::map <short, float> infraDistances;

			EventType evtType;
			Event* event;
			while (event = Com_getNextEvent())
			{
				evtType = Com_getTypeEvent(event);
				if (evtType == ET_message)
				{

					DataInterface* dEventDataInterf = Com_getMessageEventDataInterface(event);
					std::string msgId = Com_getMessageEventDataStringId(event);
					msgId = Com_getMessageEventDataStringId(event);

					//infrastructure targets
					if (msgId.find(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETSBOUNDINGBOXES) == 0)
					{
						//nothing to do for now
					}
					else if (msgId.find(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETSTRAFFICSTATES) == 0)
					{
						short targetsCount = Com_getShortData(dEventDataInterf, "targetsArrayCount");
						if (targetsCount > 0)
						{
							char fieldID[50];
							for (int targetId = 0; targetId < targetsCount; targetId++)
							{
								sprintf_s(fieldID, "targetsArray[%d]/type", targetId);
								short infraType = Com_getShortData(dEventDataInterf, fieldID);
								if (infraType == 49)
								{
									//pedestrian crossing
									sprintf_s(fieldID, "targetsArray[%d]/scanerId", targetId);
									pedestrianCrossings[Com_getShortData(dEventDataInterf, fieldID)] = true;
								}
							}
						}
					}
					else if (msgId.find(NETWORK_ISENSOR_SENSORINFRASTRUCTURETARGETS) == 0)
					{
						short targetsCount = Com_getShortData(dEventDataInterf, "targetsArrayCount");
						if (targetsCount > 0)
						{
							char fieldID[50];
							for (int targetId = 0; targetId < targetsCount; targetId++)
							{
								sprintf_s(fieldID, "targetsArray[%d]/type", targetId);
								short infraType = Com_getShortData(dEventDataInterf, fieldID);
								if (infraType == 10)
								{
									//horizontal road sign
									sprintf_s(fieldID, "targetsArray[%d]/scanerId", targetId);
									short scanerId = Com_getShortData(dEventDataInterf, fieldID);

									sprintf_s(fieldID, "targetsArray[%d]/distanceToCollision", targetId);
									float distance = Com_getFloatData(dEventDataInterf, fieldID);

									infraDistances[scanerId] = distance;
								}
							}
						}
						else
							viewer.hidePicto();
					}
					//movable targets
					else if (msgId.find(NETWORK_ISENSOR_SENSORMOVABLETARGETSBOUNDINGBOXES) == 0)
					{
						short bboxCount = Com_getShortData(dEventDataInterf, "boundingBoxesArrayCount");
						if (bboxCount > 0)
						{
							viewer.hideBoxes();
							for (int bbId = 0; bbId < bboxCount; bbId++)
							{
								char fieldID[50];

								//target ID
								sprintf_s(fieldID, "boundingBoxesArray[%d]/id", bbId);
								short targetID = Com_getShortData(dEventDataInterf, fieldID);

								//reference frame
								sprintf_s(fieldID, "boundingBoxesArray[%d]/referenceFrame", bbId);
								short refFrame = Com_getShortData(dEventDataInterf, fieldID);

								//point 1
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightX", bbId);
								double xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightY", bbId);
								double yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightZ", bbId);
								double zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 rearBottomRight(xVal, yVal, zVal);

								//point 2
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 rearTopRight(xVal, yVal, zVal);

								//point 3
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 rearbottomLeft(xVal, yVal, zVal);

								//point 4
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 rearTopLeft(xVal, yVal, zVal);

								//point 5
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 frontBottomRight(xVal, yVal, zVal);

								//point 6
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 frontTopRight(xVal, yVal, zVal);

								//point 7
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 frontbottomLeft(xVal, yVal, zVal);

								//point 8
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								stk::Vector3 frontTopLeft(xVal, yVal, zVal);

								//create the box object
								viewer.updateBoundingBox(
									ObjectBoundingBox::BBoxType::BBox_Mobile,
									targetID,
									rearBottomRight,
									rearTopRight,
									rearbottomLeft,
									rearTopLeft,
									frontBottomRight,
									frontTopRight,
									frontbottomLeft,
									frontTopLeft
									);
							}
						}
					}
					//headlight
					else if (msgId.find(NETWORK_ILIGHTSIMULATION_HEADLAMPPARAMETERS) == 0)
					{
						long lightId = Com_getLongData(dEventDataInterf, "id");
						float lightX = Com_getFloatData(dEventDataInterf, "position[0]");
						float lightY = Com_getFloatData(dEventDataInterf, "position[1]");
						float lightZ = Com_getFloatData(dEventDataInterf, "position[2]");
						float lightH = Com_getFloatData(dEventDataInterf, "orientation[0]");
						float lightP = Com_getFloatData(dEventDataInterf, "orientation[1]");
						float lightR = Com_getFloatData(dEventDataInterf, "orientation[2]");
						if (lightId == config.myLightSourceID)
						{
							viewer.updateLightSourcePosition(stk::Mark(stk::Vector3(lightX, lightY, lightZ), lightR, lightP, lightH));
						}
					}
				}
			}

			//display picto?
			std::map <short, bool>::const_iterator itCrossings;
			for (itCrossings = pedestrianCrossings.begin(); itCrossings != pedestrianCrossings.end(); ++itCrossings)
			{
				std::map <short, float>::const_iterator itDist = infraDistances.find(itCrossings->first);
				if (itDist != infraDistances.end())
				{
					if (itDist->second < 30.0)
						viewer.displayPicto();
				}
			}
		}

		viewer.update();
	}


	Process_Close();
	return 0;
}


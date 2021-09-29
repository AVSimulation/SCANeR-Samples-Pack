#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesNetwork.h"

#include "ImageSharing/ImageSharing_DLL_C.h"
#include "QtGui\qimage.h"
#include "QtCore\qstring.h"
#include "QtGui\qimagewriter.h"
#include <iostream>
#include <fstream>
#include <map>

//Main
int main(int argc, char *argv[])
{
	std::string configName = "EVAL_CAMERACAPTURE";
	std::string procName = "TARGETSDETECTION";
	for (int i = 1; i < argc; i++)
	{
		std::string currentArg(argv[i]);
		if ((currentArg == "-c") && (i + 1 < argc))
			configName = argv[i + 1];
		else if ((currentArg == "-p") && (i + 1 < argc))
			procName = argv[i + 1];
	}

	//process Com intialization
	if (Process_InitParams(procName.c_str(), configName.c_str(), 100) != 0)
	{
		std::cout << "Error while initializing SCANeR API. Exiting" << std::endl;
		return 1;
	}

	//register to SCANeR messages
	Com_registerEvent(NETWORK_ISENSOR_SENSORMOVABLETARGETSBOUNDINGBOXES);
	Com_registerEvent("LOAD");
	Com_registerEvent("UNLOAD");

	//csv result file  
	std::fstream outFile;
	char* filePath = "../../../example.csv";
	int targetNB = 0;
	int frameNb = 1;
	std::map<int, short> scenarioTargets;

	//Image Sharing
	char imgFile[100];
	ImgShData* srcImg = NULL;

	APIProcessState status = PS_DAEMON;

	while (status != PS_DEAD)
	{
		Process_Wait();
		Process_Run();
		/*! Process manager State **/
		status = Process_GetState();
		EventType evtType;
		Event* event;
		while (event = Com_getNextEvent())
		{
			evtType = Com_getTypeEvent(event);
			if (evtType == ET_state)
			{
				// STATE
				StateEventType evtStateType = Com_getStateEventType(event);
				switch (evtStateType)
				{
				case ST_Load:
				{
					//Declare image to be read
					srcImg = ImgSh_declareInputImage("CAMERASENSOR:0100000");

					//Reset Frame number
					frameNb = 1;

					//Get the number of vehicle in the scenario
					const InitialConditions* init = Com_getInitConditions(event);
					targetNB = init->vehiclesCount;
					for (int i = 0; i < targetNB; i++)
					{
						const VStruct* vehicle = Com_getInitConditionsVehicle(event, i);
						if (vehicle->id != 0) // do not record the ego
						{
							switch (vehicle->type)
							{
							case UNKNOWN_TYPE: //0
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 0));
								break;
							}
							case RIGID: //1
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 1));
								break;
							}
							case TRACTOR: //2
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 2));
								break;
							}
							case SEMI_TRAILER: //3
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 3));
								break;
							}
							case TRAILER: //4
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 4));
								break;
							}
							case CAR: //5
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 5));
								break;
							}
							case BUS: //6
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 6));
								break;
							}
							case MOTORBIKE: //7
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 7));
								break;
							}
							case BICYCLE: //8
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 8));
								break;
							}
							case PEDESTRIAN: //9
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 9));
								break;
							}
							case STATIC_OBJECT: //10
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 10));
								break;
							}
							case TRAM: //11
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 11));
								break;
							}
							case TRAIN: //12
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 12));
								break;
							}
							case ALIVEBEING: //13
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 13));
								break;
							}
							case AIRPLANE: //14
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 14));
								break;
							}
							case CNT_VEHICLETYPE: //15
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 15));
								break;
							}
							default:
							{
								scenarioTargets.insert(std::pair<int, short>(vehicle->id, 0));
								break;
							}
							}
						}

						for (std::map<int, short>::const_iterator itTargets = scenarioTargets.begin(); itTargets != scenarioTargets.end(); ++itTargets)
						{
							std::cout << "Element[" << itTargets->first << "]: " << itTargets->second << std::endl;
						}
					}
					//Delete old csv file
					remove(filePath);
					//Open csv file 
					outFile.open(filePath, std::ofstream::app);
					//Write first line
					outFile << "Frame Number, Time, ID, Type, ";
					outFile << "BBox_rearBottomRightX, BBox_rearBottomRightY, ";
					outFile << "BBox_rearTopRightX, BBox_rearTopRightY, ";
					outFile << "BBox_rearBottomLeftX, BBox_rearBottomLeftY, ";
					outFile << "BBox_rearTopLeftX, BBox_rearTopLeftY, ";
					outFile << "BBox_frontBottomRightX, BBox_frontBottomRightY, ";
					outFile << "BBox_frontTopRightX, BBox_frontTopRightY, ";
					outFile << "BBox_frontBottomLeftX, BBox_frontBottomLeftY, ";
					outFile << "BBox_frontTopLeftX, BBox_frontTopLeftY, ";
					outFile << std::endl;
					//End first line
					Com_validateStateEvent(event);
					break;
				}
				case ST_Unload:
				{
					//Close the csv file
					outFile.close();
					//Delete images
					ImgSh_deleteAllImages();
					Com_validateStateEvent(event);
					break;
				}
				default:
				{
					Com_validateStateEvent(event);
					break;
				}
				}
			}
			// MESSAGE
			if (evtType == ET_message)
			{
				DataInterface* dEventDataInterf = Com_getMessageEventDataInterface(event);
				std::string msgId = Com_getMessageEventDataStringId(event);

				// Movable targets BBox
				if (msgId.find(NETWORK_ISENSOR_SENSORMOVABLETARGETSBOUNDINGBOXES) == 0)
				{
					short vhlId = Com_getShortData(dEventDataInterf, "vhlId");
					if (vhlId == 0)
					{
						short bboxCount = Com_getShortData(dEventDataInterf, "boundingBoxesArrayCount");
						if (bboxCount > 0)
						{
							for (int bbId = 0; bbId < bboxCount; bbId++)
							{
								outFile << frameNb << "," << Process_GetTime() << ",";

								char fieldID[50];

								//target ID
								sprintf_s(fieldID, "boundingBoxesArray[%d]/id", bbId);
								short targetID = Com_getShortData(dEventDataInterf, fieldID);

								//find target type from target ID
								std::map<int, short>::iterator itTarget = scenarioTargets.find(targetID);
								short targetType = itTarget->second;

								outFile << targetID << "," << targetType << ",";

								//point 1
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightX", bbId);
								double xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightY", bbId);
								double yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearBottomRightZ", bbId);
								double zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 2
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 3
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearbottomLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 4
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/rearTopLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 5
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontBottomRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 6
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopRightZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 7
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontbottomLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								//point 8
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftX", bbId);
								xVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftY", bbId);
								yVal = Com_getDoubleData(dEventDataInterf, fieldID);
								sprintf_s(fieldID, "boundingBoxesArray[%d]/frontTopLeftZ", bbId);
								zVal = Com_getDoubleData(dEventDataInterf, fieldID);
								outFile << xVal << "," << yVal << ",";

								outFile << std::endl;
							}

							//Update input image 
							ImgSh_updateInputImages();
							if (srcImg == NULL)
							{
								std::cout << "Empty image from sensor" << std::endl;
								break;
							}
							//Write image - Image Sharing API image is an 8 bit image
							QImage outImage((const unsigned char*)srcImg->myImgRawData, srcImg->myHeader.myImageWidth, srcImg->myHeader.myImageHeight, QImage::Format_RGB888);
							sprintf(imgFile, "..\\..\\..\\Capture\\frame%d.png", frameNb);
							//Reverse image 
							QImage reversedOutImage = outImage.mirrored(false, true);
							//Save Image
							if (reversedOutImage.save(imgFile))
							{
								std::cout << "Image Saved in : " << imgFile << std::endl;
							}
							// END OF BBOX 
						}
					}
					//Increase the frame number
					frameNb++;
					break;
				}
			}
		} //WHILE GET NEXT EVENT
	} //WHILE PS_DEAD

	Process_Close();

	return 0;
} //MAIN


#include "VEN/VEN2.h"
#include "ScanerAPI\scanerAPI_DLL_C.h"
#include "ScanerAPI\scanerAPI_DLL_Enums.h"
#include "ScanerAPI\ScanerAPImessagesNetwork.h"

#include <string>
#include <iostream>

#define DATA_IN_SIZE 1

int main(int argc, char** argv)
{
	std::string dataIn[DATA_IN_SIZE];

	VENCom* venCom = VENCreate();
	
	Process_Init(argc, argv);
	DataInterface* toVisual = Com_declareOutputData(NETWORK_IINFORMATION_SENDVISUALCONSTANTTEXTMESSAGE);

	VENInit(venCom, "239.255.0.1", 63999, VENSendNonBuffered);

	APIProcessState status = PS_DAEMON;

	while(status != PS_DEAD)
	{
		Process_Wait();
		Process_Run();
		status = Process_GetState();

		if (status == PS_RUNNING)
		{
			while (VENMessageAvailable(venCom, "VENPROGRAM", "TOVISUAL") == 0)
			{
			}

			if (VENMessageRead(venCom, "VENPROGRAM", "TOVISUAL", VENTypeString, dataIn, DATA_IN_SIZE) == 0)
			{
				Com_setStringData(toVisual, "constantString", dataIn[0].c_str());
				Com_setStringData(toVisual, "displayAreaName", "LEFT");
			}
			Com_updateOutputs(UT_NetworkData);
		}
	}
	Process_Close();
	VENRelease(venCom);
	return 0;
}
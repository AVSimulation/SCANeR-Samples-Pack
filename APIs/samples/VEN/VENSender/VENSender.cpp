#include "VEN/VEN2.h"

#include <string>
#include <iostream>
#include "Windows.h"

#define DATA_OUT_SIZE 256

int main(int argc, char** argv)
{
	std::string dataOut[DATA_OUT_SIZE];

	VENCom* venCom = VENCreate();

	VENInit(venCom, "239.255.0.1", 63999, VENSendNonBuffered);
	std::string msg;
	int i = 0;
	while(1)
	{
		Sleep(10);
		msg = "VENMSG";
		msg.append(std::to_string(i));
		dataOut[0] = msg;
		VENMessageWrite(venCom, "VENPROGRAM", "TOVISUAL", VENTypeString, dataOut, DATA_OUT_SIZE);
		msg.clear();
		i++;
	}

	VENRelease(venCom);
	return 0;
}
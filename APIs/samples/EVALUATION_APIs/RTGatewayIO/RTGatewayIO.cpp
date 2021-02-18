//project includes
#include "UDPProtocol.h"

//C/C++ includes
#include <iostream>
#include <string.h>


//DOUBLE UDP INPUT INDEXES (made to receive the UDP Filter outputs)
#define VehicleUpdate0_pos_x 0
#define VehicleUpdate0_pos_y 1
#define VehicleUpdate0_pos_z 2
#define VehicleUpdate0_pos_h 3
#define VehicleUpdate0_pos_p 4
#define VehicleUpdate0_pos_r 5
#define VehicleUpdate0_speed_x 6
#define VehicleUpdate0_speed_y 7
#define VehicleUpdate0_speed_z 8
#define VehicleUpdate0_speed_h 9
#define VehicleUpdate0_speed_p 10
#define VehicleUpdate0_speed_r 11
#define VehicleUpdate1_pos_x 12
#define VehicleUpdate1_pos_y 13
#define VehicleUpdate1_pos_z 14
#define VehicleUpdate1_pos_h 15
#define VehicleUpdate1_pos_p 16
#define VehicleUpdate1_pos_r 17
#define VehicleUpdate1_speed_x 18
#define VehicleUpdate1_speed_y 19
#define VehicleUpdate1_speed_z 20
#define VehicleUpdate1_speed_h 21
#define VehicleUpdate1_speed_p 22
#define VehicleUpdate1_speed_r 23
#define GPS_200000_globalId 24
#define GPS_200000_latitude 25
#define GPS_200000_longitude 26

//DOUBLE UDP OUTPUT INDEXES (made to send the UDP packets to SCANeR Export Channels)

#define NB_DBL_OUT	3

#define DOUBLE_OUT_A 0
#define DOUBLE_OUT_B 1
#define DOUBLE_OUT_C 2

/**********************************************************************************************/
/* This sample demonstrates how to receive and send UDP packets using the RT_GATEWAY module	  */
/* To use this sample, you need to open the EVAL_DATAEXCHANGE scenario						  */
/**********************************************************************************************/

int main(int argc, char* argv[])
{
	short localPort = 8192; // default port
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-port") == 0 && (i + 1 < argc))
			localPort = (short)atoi(argv[i + 1]);
	}

	UDPSocket* sckt = newUDPSocketServer(localPort);
	sckt->setBlocking(true);
	if (sckt->good())
	{
		std::cout << "Listening on port: " << localPort << std::endl;
	}
	else
	{
		std::cout << "Error opening socket: " << localPort << std::endl;
		return 2;
	}

	int nbInPackets = 0;
	while (true)
	{
		double inDbl[NB_DBL_IN_MAX];
		int nbDbl;
		while (recieveUDPPacket(sckt, inDbl, nbDbl)) // Receive UDP packets in a buffer
		{
			nbInPackets++;
			system("CLS");
			std::cout << "Packet " << nbInPackets << '\n';
			std::cout << "DS3 LATITUDE: " << inDbl[GPS_200000_latitude] << '\n';
			std::cout << "DS3 LONGITUDE: " << inDbl[GPS_200000_longitude] << '\n';
			std::cout << "DS3 SPEED (m/s): " << inDbl[VehicleUpdate0_speed_x] << '\n';
			std::cout << "FORD ESCAPE SPEED (m/s): " << inDbl[VehicleUpdate1_speed_x] << '\n';
			std::cout << "------------------------------------------------------------------------ " << std::flush;
		};

		double outDbl[NB_DBL_OUT];
		outDbl[DOUBLE_OUT_A] = 0.01;
		outDbl[DOUBLE_OUT_B] = 0.02;
		outDbl[DOUBLE_OUT_C] = 3;
		sendUDPPacket(sckt, outDbl, NB_DBL_OUT); // Send UDP packets (received on Export Channel into SCANeR)
	};
	delete sckt;
	return 0;
}

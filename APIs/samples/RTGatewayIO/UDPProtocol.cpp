#include "UDPProtocol.h"

void sendUDPPacket(UDPSocket* s, double* dblData, int numberDbl)
{
	int bufferSize = sizeof(double)*numberDbl;
	double* buffer = new double[bufferSize];

	for (int i = 0; i<numberDbl; i++)
		buffer[i] = dblData[i];

	s->send(buffer, bufferSize);
	delete[] buffer;
}


bool recieveUDPPacket(UDPSocket* s, double* inDbl, int& nbDbl)
{
	double buffer[NB_DBL_IN_MAX];

	int rcvSize = s->receive(buffer, NB_DBL_IN_MAX*sizeof(double));
	if (rcvSize < (int) sizeof(double))
		return false;

	nbDbl = rcvSize / sizeof(double);
	
	for (int i = 0; i < nbDbl; i++)
		inDbl[i] = buffer[i];

	return true;
}

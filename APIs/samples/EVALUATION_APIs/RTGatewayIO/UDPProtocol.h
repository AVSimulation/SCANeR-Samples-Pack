#pragma once

#include "UDPSocket.h"

// Copyright Oktal SA,
// These functions format the messages sent/recieves by RT_GATEWAY UDP protocol
// Reuse these functions in a program to receive and send data from (to) SCANeR without SCANeR API dependecies

#define NB_DBL_IN_MAX 27

void sendUDPPacket(UDPSocket* s, double* dblData, int numberDbl);
bool recieveUDPPacket(UDPSocket* s, double* inDbl, int& nbDbl);


#pragma once

#include <string>

int getHostName(std::string& name);

//UDP socket class to hide implementation differences between platforms
//and the socket API complexities
class UDPSocket
{
public:
	virtual ~UDPSocket() {}

	//returns true if the socket was successfully opened
	virtual bool good() = 0;

	//sets the socket as blocking or non blocking
	//this method should only be called once, before any packet has been sent/recieved
	virtual void setBlocking(bool IsBlocking) = 0;

	//for a blocking socket, set the timeout befor returning an error apon recieve
	virtual bool setTimeout(double Timeout) = 0;

	//recieve a packet, buffer must be allocated by the caller, the "size" parameter defines the buffer siez
	//this function returns the size of the receieved plugin or -1 if no packet was recieved
	virtual int receive(void* buffer, int size) = 0;

	//send a packet using the contents in "buffer" with size "size"
	virtual bool send(void* buffer, int size) = 0;

	//get total bytes sent on this socket (for statistics purposes)
	virtual int getTotalBytesSent() = 0;

	//get total bytes receieved on this socket (for statistics purposes)
	virtual int getTotalBytesReceived() = 0;

	//reset statistics done by "getTotalBytesSent()" "getTotalBytesReceieved()"
	virtual void resetStatistics() = 0;
};

//open a port on the local host, messages sent on this socket
//will be sent back to the sender of the last message recieved
UDPSocket* newUDPSocketServer(short portno);

//open a socket to connect to "servername" host on remote port "portno"
//the local port is a free port as determined by the OS
UDPSocket* newUDPSocketClient(const char *servername, short portno, short localport);

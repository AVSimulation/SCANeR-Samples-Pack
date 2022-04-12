
#ifdef _WIN32

#pragma warning( disable : 4786 ) //disable "identifier name too long" warning


extern "C" int errno;

#include <winsock2.h>

//#include <io.h>

#include <iostream>
#include <string.h>

#define DATA_T char
#define SOCKLEN_T int

#include "cal_reseau.h"

//UTILS
void write_error(const char* where, bool bad=true)
{
	if (bad)
	{
		const char* errortext = strerror(errno);
		std::cout << "error(" << __FILE__ << "," << where << "): " << errortext << std::endl;
		int error = WSAGetLastError();
		std::cout << "WSAGetLastError() returned " << error << std::endl;
	}
}

void InitBigBuf(int s)
{
	int intopt = 40000;
	int ret = setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);

	intopt = 40000;
	ret = setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);
}

//feinte pour initializer et netoyer winsock
struct initsock
{
	initsock()
	{
		WSADATA WSAData;
		WSAStartup(MAKEWORD(1,1), &WSAData);
	}
	~initsock()
	{
		WSACleanup();
	}
} initsock;

void SetBlockingSocket(int s, bool IsBlocking)
{
	if (IsBlocking)
	{
		int ret = ioctlsocket(s, FIONBIO, 0);
		write_error("set blocking",ret!=0);
	}
	else
	{
		unsigned long nonzero = 1;
		int ret = ioctlsocket(s, FIONBIO, (unsigned long*)&nonzero);
		write_error("set nonblocking",ret!=0);
	}
}

//pour exporter gethostname et ne pas etre oblige de lier avec winsock dans l'exe
int HGetHostName(char* name, int namelen)
{
	return gethostname(name, namelen);
}


//CLASS HSocServer
HSocServer::HSocServer(short portno)
{
//open socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	write_error("socket creation",s==INVALID_SOCKET);
	if (s==INVALID_SOCKET)
		return;

//bind
	sockaddr_in name;
	name.sin_family = AF_INET;
	name.sin_port = htons(portno);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(s, (sockaddr*)&name, sizeof(name));
	//write_error("bind",ret!=0);
	//cout << "waiting on port: " << portno << endl;
	if (ret!=0)
	{
		std::cout << "network error: impossibe to open port number " << portno << std::endl;
		s = INVALID_SOCKET;
		return;
	}

//voir les proprietees du socket
	//BOOL boolopt;
	//int intopt;
	//int optlen;

//activer TCP_NODELAY pour les applications interactives
	//boolopt = 1;
	//ret = setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)&boolopt, sizeof(BOOL));
//mettre un gros buffer pour la reception des packets
	int intopt = 80000;
	ret = setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);

//jeter un coup d'oeil aux options
	//optlen = sizeof(BOOL);
	//ret = getsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)&boolopt, &optlen);
	//optlen = sizeof(int);
	//ret = getsockopt(s, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)&intopt, &optlen);
	//ret = getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&intopt, &optlen);
	//ret = getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&intopt, &optlen);

	InitBigBuf(s);
}

HSocServer::~HSocServer()
{
	closesocket(s);
}

bool HSocServer::good()
{
	return s!=INVALID_SOCKET;
}

void HSocServer::SetBlocking(bool IsBlocking)
{
	SetBlockingSocket(s,IsBlocking);
}

bool HSocServer::SetTimeout(double Timeout)
{
	int intopt = int(Timeout*1000);
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&intopt, sizeof(int))==0;
}

//BUG un seul client pour l'instant
static sockaddr ClientAdresses;

int HSocServer::Recieve(void* buffer, int size)
{
//read incomming
	sockaddr from;
	SOCKLEN_T fromlen = sizeof(from);
	int recieved_bytes = recvfrom(s,  (DATA_T*)buffer, size, 0, &from, (SOCKLEN_T*)&fromlen);
	if (recieved_bytes>0)
	{
		ClientAdresses = from;
		return recieved_bytes;
	}
	return -1;
}

bool HSocServer::Send(void* buffer, int size)
{
	int sent_bytes = sendto(s,  (DATA_T*)buffer, size, 0, &ClientAdresses, sizeof(ClientAdresses));
	return (sent_bytes==size);
}


//CALSS HSocClient
HSocClient::HSocClient(const char *servername, short portno) :
	servername(servername),
	TotalBytesSent(0),
	TotalBytesRecieved(0)
{
	int ret;

//open socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	write_error("socket creation",s==INVALID_SOCKET);
	if (s==INVALID_SOCKET)
		return;

//get the server adress
	hostent *mmserv = gethostbyname(servername);
	//write_error("gethostbyname",mmserv==0);
	if (mmserv==0)
	{
		std::cout << "network error: cannot find host \"" << servername << "\"" << std::endl;
		s = INVALID_SOCKET;
		return;
	}
	sockaddr_in name;
	memcpy((char*)(&(name.sin_addr.s_addr)), mmserv->h_addr, mmserv->h_length);
	name.sin_family = AF_INET;
	name.sin_port = htons(portno);

//connect
	ret = connect(s, (sockaddr*)&name, sizeof(name));
	write_error("connect",ret!=0);
	if (ret!=0)
		s = INVALID_SOCKET;

//mettre un gros buffer pour la reception des packets
	/*int intopt = 40000;
	ret = setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);*/
	InitBigBuf(s);
}

HSocClient::~HSocClient()
{
	closesocket(s);
}

bool HSocClient::good()
{
	return s!=INVALID_SOCKET;
}

void HSocClient::SetBlocking(bool IsBlocking)
{
	SetBlockingSocket(s,IsBlocking);
}

bool HSocClient::SetTimeout(double Timeout)
{
	int intopt = int(Timeout*1000);
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&intopt, sizeof(int))==0;
}

bool HSocClient::Send(void* buffer, int size)
{
	int sent_bytes = send(s, (DATA_T*)buffer, size, 0);
	write_error("sending bytes",sent_bytes!=size);
	TotalBytesSent += sent_bytes;
	return sent_bytes==size;
}


int HSocClient::Recieve(void* buffer, int size)
{
	int recv_bytes = recv(s, (DATA_T*)buffer, size, 0);
	if (recv_bytes<=0)
		return -1;
	TotalBytesRecieved += recv_bytes;
	return recv_bytes;
}


#endif //_WIN32
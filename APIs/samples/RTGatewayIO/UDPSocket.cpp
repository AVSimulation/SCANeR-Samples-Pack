
#include "UDPSocket.h"
#ifdef WIN32
#include <winsock2.h>
#define SOCKLEN_T int
#else
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
typedef int SOCKET;
#define INVALID_SOCKET -1
#define SOCKLEN_T socklen_t
#endif
#include <iostream>
#include <string.h>

#define DATA_T char


int getHostName(std::string& name)
{
	char host[FILENAME_MAX];
	int ret = gethostname(host, FILENAME_MAX);
	name = host;
	return ret;
}


//an unique id is assigned to each client  
class UDPSocketServer : public UDPSocket
{
public:
	UDPSocketServer(short portno);
	virtual ~UDPSocketServer();
	virtual bool good();
	//apparament SetBlocking ne marche qu'une seul fois au debut
	//pour UDPSocketServer, il faut donc choisir une fois pour toute blocking ou pas...
	//je ne sais pas pourquoi
	virtual void setBlocking(bool IsBlocking);
	virtual bool setTimeout(double Timeout);
	virtual int receive(void* buffer, int size);
	virtual bool send(void* buffer, int size);

	virtual int getTotalBytesSent() {return totalBytesSent;}
	virtual int getTotalBytesReceived() {return totalBytesReceived;}
	virtual void resetStatistics() {totalBytesSent=0; totalBytesReceived=0;}
private:
	int totalBytesSent;
	int totalBytesReceived;
	SOCKET s;
};

class UDPSocketClient : public UDPSocket
{
public:
	UDPSocketClient(const char *servername, short portno, short localport);
	virtual ~UDPSocketClient();
	virtual bool good();
	virtual void setBlocking(bool IsBlocking);
	virtual bool setTimeout(double Timeout);
	virtual int receive(void* buffer, int size);
	virtual bool send(void* buffer, int size);

	virtual int getTotalBytesSent() {return totalBytesSent;}
	virtual int getTotalBytesReceived() {return totalBytesRecieved;}
	virtual void resetStatistics() {totalBytesSent=0; totalBytesRecieved=0;}
private:
	int totalBytesSent;
	int totalBytesRecieved;
	SOCKET s;
};

//UTILS
void write_error(const char *where, bool bad=true)
{
	if (bad)
	{
#ifdef WIN32
		const char* errortext = strerror(errno);
		std::cout << "error(" << __FILE__ << "," << where << "): " << errortext << std::endl;
		int error = WSAGetLastError();
		std::cout << "WSAGetLastError() returned " << error << std::endl;
#else
        perror("socket error: ");
        std::cout << "error(" << __FILE__ << "," << where << "): " << std::endl;
#endif
	}
}

void InitBigBuf(SOCKET s)
{
	int intopt = 40000;
	int ret = setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);

	intopt = 40000;
	ret = setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&intopt, sizeof(int));
	write_error("setsockopt",ret!=0);
}

//feinte pour initializer et netoyer winsock
#ifdef WIN32
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
#endif

void SetBlockingSocket(SOCKET s, bool IsBlocking)
{
    if (s < 0) return;

 #ifdef WIN32
    unsigned long mode = IsBlocking ? 0 : 1;
    ioctlsocket(s, FIONBIO, &mode);
 #else
    int flags = fcntl(s, F_GETFL, 0);
    if (flags < 0) return;
    flags = IsBlocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
    fcntl(s, F_SETFL, flags);
 #endif
}


//CLASS UDPSocketServer
UDPSocketServer::UDPSocketServer(short portno) :
	s(0),
	totalBytesSent(0),
	totalBytesReceived(0)
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

UDPSocketServer::~UDPSocketServer()
{
#ifdef WIN32
	closesocket(s);
#else
    close(s);
#endif
}

bool UDPSocketServer::good()
{
	return s!=INVALID_SOCKET;
}

bool UDPSocketServer::setTimeout(double Timeout)
{
	int intopt = int(Timeout*1000);
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&intopt, sizeof(int))==0;
}

void UDPSocketServer::setBlocking(bool IsBlocking)
{
	SetBlockingSocket(s,IsBlocking);
}

//BUG un seul client pour l'instant
static sockaddr ClientAdresses;

int UDPSocketServer::receive(void* buffer, int size)
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

bool UDPSocketServer::send(void* buffer, int size)
{
	int sent_bytes = sendto(s,  (DATA_T*)buffer, size, 0, &ClientAdresses, sizeof(ClientAdresses));
	return (sent_bytes==size);
}


//CALSS UDPSocketClient
UDPSocketClient::UDPSocketClient(const char *servername, short portno, short localport) :
	totalBytesSent(0),
	totalBytesRecieved(0)
{
	int ret;

//open socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	write_error("socket creation",s==INVALID_SOCKET);
	if (s==INVALID_SOCKET)
		return;

	sockaddr_in nameloc;
	nameloc.sin_family = AF_INET;
	nameloc.sin_port = htons(localport);
	nameloc.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(s, (sockaddr*)&nameloc, sizeof(nameloc));
	if (ret != 0)
	{
		std::cout << "network error: impossibe to bind to port number " << localport << std::endl;
		s = INVALID_SOCKET;
		return;
	}


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

UDPSocketClient::~UDPSocketClient()
{
#ifdef WIN32
	closesocket(s);
#else
    close(s);
#endif
}

bool UDPSocketClient::good()
{
	return s!=INVALID_SOCKET;
}

void UDPSocketClient::setBlocking(bool IsBlocking)
{
	SetBlockingSocket(s,IsBlocking);
}

bool UDPSocketClient::setTimeout(double Timeout)
{
	int intopt = int(Timeout*1000);
	return setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&intopt, sizeof(int))==0;
}

bool UDPSocketClient::send(void* buffer, int size)
{
	int sent_bytes = ::send(s, (DATA_T*)buffer, size, 0);
	write_error("sending bytes",sent_bytes!=size);
	totalBytesSent += sent_bytes;
	return sent_bytes==size;
}


int UDPSocketClient::receive(void* buffer, int size)
{
	int recv_bytes = recv(s, (DATA_T*)buffer, size, 0);
	if (recv_bytes<=0)
		return -1;
	totalBytesRecieved += recv_bytes;
	return recv_bytes;
}

UDPSocket* newUDPSocketServer(short portno)
{
	return new UDPSocketServer(portno);
}

UDPSocket* newUDPSocketClient(const char* servername, short portno, short localport)
{
	return new UDPSocketClient(servername, portno, localport);
}

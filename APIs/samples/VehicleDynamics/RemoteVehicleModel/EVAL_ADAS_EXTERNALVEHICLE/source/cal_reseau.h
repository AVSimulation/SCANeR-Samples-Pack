
#pragma once

#include <string>

int HGetHostName(char* name, int namelen);

//an unique id is assigned to each client  
class HSocServer
{
public:
	HSocServer(short portno);
	~HSocServer();
	bool good();
//apparament SetBlocking ne marche qu'une seul fois au debut
//pour HSocServer, il faut donc choisir une fois pour toute blocking ou pas...
//je ne sais pas pourquoi
	void SetBlocking(bool IsBlocking);
	bool SetTimeout(double Timeout);
	int Recieve(void* buffer, int size);
	bool Send(void* buffer, int size);
private:
	unsigned int s;
};

class HSocClient
{
public:
	HSocClient(const char *servername, short portno);
	~HSocClient();
	bool good();
	void SetBlocking(bool IsBlocking);
	bool SetTimeout(double Timeout);
	int Recieve(void* buffer, int size);
	bool Send(void* buffer, int size);

	inline const char* GetServerName() {return servername.c_str();}
	inline int GetTotalBytesSent() {return TotalBytesSent;}
	inline int GetTotalBytesRecieved() {return TotalBytesRecieved;}
	inline void ResetStatistics() {TotalBytesSent=0; TotalBytesRecieved=0;}
private:
	std::string servername;
	int TotalBytesSent;
	int TotalBytesRecieved;
	unsigned int s;
};

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#define maxi 30
typedef char* str;

class Socket
{
public:
	Socket(int port);
	Socket(char* serverIP, int port);
	int Send(char* data);
	int Recv(char* buff, int size);
	int SendOneByte(char data);
	int Get_Content_Length(char* name);
	int stringfind(str strsrc, str strfind);
	int status(str strsrc, str strfind, char arr[], char key);
	void SocketTransfer(char* dataRecv, int sizeData);
private:
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
};



#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket.h"
#include "stdio.h"

Socket::Socket(int port)
{
	printf("Initialising Winsock... \r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : % d \r\n", WSAGetLastError());
	}
	printf(" Initialised.\r\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d", WSAGetLastError());
	}
	else
	{
		printf(" Socket created.\r\n");

		server.sin_addr.s_addr = htonl(INADDR_ANY);
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		bind(s, (struct sockaddr*)&server, sizeof(struct sockaddr)); //declare port of server
	}
}

void Socket::SocketTransfer(char* dataRecv, int sizeData)
{
	listen(s, 10);
	struct sockaddr_in client;
	int lenSockAddr = sizeof(struct sockaddr);
	SOCKET sock = accept(s, (struct sockaddr*)&client, &lenSockAddr);
	memset(dataRecv, 0, sizeData);
	recv(sock, dataRecv, sizeData, 0);
	//printf("data: %s\r\n", dataRecv);
	char* dataSend = (char*)"200 OK";
	send(sock, dataSend, strlen(dataSend), 0);
	closesocket(sock);

}

Socket::Socket(char* serverIP, int port)
{
	printf("Initialising Winsock...\r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : %d\r\n", WSAGetLastError());
	}

	printf(" Initialised.\r\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not cre ate socket : %d\r\n", WSAGetLastError());
	}

	printf(" Socket created.\r\n");

	server.sin_addr.s_addr = inet_addr(serverIP);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(s, (struct sockaddr*)&server, sizeof(server)), 0)
	{
		printf("connect error\r\n");
	}

	printf("Connected\r\n");
}
int Socket::Send(char* data)
{
	int size = 0;
	while (data[size++] != '\0');
	return send(s, data, (size - 1), 0);
}

int Socket::Recv(char* buff, int size)
{
	return recv(s, buff, size, 0);
}

int Socket::SendOneByte(char data)
{
	return send(s, &data, 1, 0);
}

int Socket::Get_Content_Length(char* name)
{
	char* msg = (char*)"Content-Length: ";
	char* num = 0;
	char arr[maxi];
	status(name, msg, arr, '\r');
	return (atoi(arr));
}

int Socket::stringfind(str strsrc, str strfind)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < strlen(strsrc) - strlen(strfind); i++)
	{
		for (j = 0; j < strlen(strfind); j++)
		{
			if (strsrc[i + j] != strfind[j]) break;
		}
		if (j == strlen(strfind)) break;
	}
	if (i == strlen(strsrc) - strlen(strfind)) return -1;
	return i + strlen(strfind);
}

int Socket::status(str strsrc, str strfind, char arr[], char key)
{
	int i = 0;
	int j = 0;
	int index = 0;
	for (i = stringfind(strsrc, strfind); strsrc[i] != key; i++)
	{
		arr[j++] = strsrc[i];
		index = j;
	}
	while (index < maxi)
	{
		arr[index] = 0;
		index++;
	}
	return 0;
	if (strsrc[i] == ' ') return -1;
}


#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"

class AWS_S3 : private Socket
{
public:
	AWS_S3();
	void get(char* nameFile, char* buff, int buffLen);
	void put(char* nameFile, char* data, int dataLen);
	void putFile(char* nameFile);
	void getFile(char* nameFile);
};




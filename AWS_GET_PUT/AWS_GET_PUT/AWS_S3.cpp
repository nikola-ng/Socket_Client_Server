#include "AWS_S3.h"

AWS_S3::AWS_S3() :Socket((char*)"52.219.128.83", 80)
{

}

void AWS_S3::get(char* nameFile, char* buff, int buffLen)
{
	char dataSend[1024];
	sprintf(dataSend, "GET /%s HTTP/1.1\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameFile);

	Send(dataSend);
	char header[1024];
	memset(header, 0, sizeof(header));
	int count = 0;
	while (1)
	{
		Recv(header + count, 1);
		if (count > 3)
		{
			if (header[count] == '\n' && header[count - 1] == '\r'
				&& header[count - 2] == '\n' && header[count - 3] == '\r')
			{
				break;
			}
		}
		count++;
	}
	printf("Header: \r\n%s", header);
	Recv(buff, buffLen);
	printf("\r\n");
}

void AWS_S3::put(char* nameFile, char* data, int dataLen)
{
	char dataSend[1024];
	sprintf(dataSend, "PUT /%s HTTP/1.1\r\nContent-Length: %d\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n%s", nameFile, dataLen, data);
	printf("Data Send: %s\r\n", dataSend);

	Send(dataSend);
	printf("\r\n");
}

void AWS_S3::putFile(char* nameFile)
{
	FILE* file = fopen(nameFile, "a+b");
	int sizeFile = 0;
	while (true)
	{
		if (fgetc(file) == EOF) break;
		sizeFile++;
	}
	fclose(file);
	printf("Size of file: %d\r\n", sizeFile);

	char header[256];
	memset(header, 0, sizeof(header));
	sprintf(header, "PUT /%s HTTP/1.1\r\nContent-Length: %d\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameFile, sizeFile);
	printf("%s", header);
	Send(header);

	file = fopen(nameFile, "a + b");
	char temp = 0;
	for (int i = 0; i < sizeFile; i++)
	{
		temp = fgetc(file);
		SendOneByte(temp);
	}
	char dataRecv[1024];
	memset(dataRecv, 0, sizeof(dataRecv));
	Recv(dataRecv, sizeof(dataRecv));
	printf("%s", dataRecv);
}

void AWS_S3::getFile(char* nameFile)
{
	char data_send[1024];
	memset(data_send, 0, 1024);
	sprintf(data_send, "GET /%s HTTP/1.1\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameFile);
	Send(data_send);

	char temp[1024];
	memset(temp, 0, 1024);
	Recv(temp, sizeof(temp));
	int contenLen = Get_Content_Length(temp);
	printf("%s\r\n", temp);
	printf("Size of Content-Length: %d\r\n", contenLen);

	FILE* file = fopen(nameFile, "w+b");
	char data_char = 0;
	for (int i = 0; i < contenLen; i++)
	{
		Recv(&data_char, sizeof(data_char));
		fputc(data_char, file);
	}
	fclose(file);
}
#include "Socket.h"
#include "AWS_S3.h"
#include <Windows.h>
#include <thread>

void thread_1()
{
	while (true)
	{
		printf("Hello\r\n");
		Sleep(1000);
	}
}

void thread_2()
{
	while (true)
	{
		printf("Xin Chao\r\n");
		Sleep(1000);
	}
}
int main()
{
	//Socket test((char*)"192.168.1.20", 2222);
	////test.Send((char*)"Send from my device\r\n");
	//char buff[1024];
	//test.Recv(buff, sizeof(buff));
	////printf("Hello");

	AWS_S3 imic;
	//char buffer[1024];
	//memset(buffer, 0, sizeof(buffer));
	//imic.get((char*)"helloWorld.txt", buffer, sizeof(buffer));
	//printf("%s", buffer);

	//// Put
	//char* data = (char*)"xin chao";
	//imic.put((char*)"test_IMIC.txt", data, strlen(data));
	//imic.putFile((char*)"test.txt");
	//imic.putFile((char*)"demo_put.jpg");
	//imic.getFile((char*)"demo_put.jpg");

	//std::thread vn(thread_1);
	//std::thread eng(thread_2);
	//vn.join();
	//eng.join();

	Socket server(1234);
	while (1)
	{
		char data[1024];
		memset(data, 0, sizeof(data));
		server.SocketTransfer(data, sizeof(data));
		printf("\r\nBuff: %s\r\n", data);
		for (int i = 3; i < strlen(data); i++)
		{
			if (data[i] == 'F' && data[i - 1] == 'F' && data[i - 2] == 'O')
			{
				imic.put((char*)"hellowWorld.txt", (char*)"LED_OFF", 7);
				break;
			}
			else if (data[i] == 'N' && data[i - 1] == 'O')
			{
				imic.put((char*)"hellowWorld.txt", (char*)"LED_ON", 7);
				break;
			}
		}
	}
	return 0;
}
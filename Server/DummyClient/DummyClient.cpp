#include "pch.h"
#include <iostream>

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << "Socket ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData	 wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	SOCKADDR_IN	serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);	// host to network short

	// Conntected UDP
	::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	while (true)
	{
		// TODO
		char sendBuffer[100] = "HelloWorld";

		// Unconnected UDP
		//int32 resultCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		// Conntected UDP
		int32 resultCode = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
		if (resultCode == SOCKET_ERROR)
		{
			HandleError("Socket");
			return 0;
		}

		cout << "SendData! Len = " << sizeof(sendBuffer) << endl;

		SOCKADDR_IN recvAddr;
		::memset(&recvAddr, 0, sizeof(recvAddr));
		int32 addrLen = sizeof(recvAddr);

		char recvBuffer[1000];
		//int32 recvLen = ::recvfrom(clientSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&recvAddr, &addrLen);
		
		int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		if (recvLen <= 0)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Socket ErrorCode : " << errCode << endl;
			return 0;
		}

		cout << "Recv Data! Data = " << recvBuffer << endl;
		cout << "Recv Data! Len = " << recvLen << endl;

		this_thread::sleep_for(1s);
	}

	// -------------------------
	::closesocket(clientSocket);

	::WSACleanup();
}
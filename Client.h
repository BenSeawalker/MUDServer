#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <WS2tcpip.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


class Client
{
public:
	Client();
	~Client();
	
	SOCKET ConnectSocket;
	UINT Client_ID;

	void Disconnect();


	int ReceivePacket(Packet * _packet);
};


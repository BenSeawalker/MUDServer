#pragma once
#include <WinSock2.h>
#include <Windows.h>

class NetworkServices
{
public:
	static int sendMessage(SOCKET _curSocket, char * _message, int _messageSize);
	static int receiveMessage(SOCKET _curSocket, char * _buffer, int _bufferSize);
};


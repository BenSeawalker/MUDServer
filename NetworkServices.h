#pragma once
#include <WinSock2.h>
#include <Windows.h>

#include "NetworkData.h"

class NetworkServices
{
public:
	static int SendPacket(SOCKET _socket, PacketTypes _type, char * _data, UINT _size);
	static int SendPacket(SOCKET _socket, Packet * _packet);
	static int ReceivePacket(SOCKET _socket, Packet * _packet);

	static Packet * CreatePacket(PacketTypes _type, char * _data, UINT _dataSize);

	static char * SerializeData(void * _data);
};


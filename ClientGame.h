#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class ClientGame
{
public:
	ClientGame();
	~ClientGame();

	ClientNetwork * network;
	
	char network_data[MAX_PACKET_SIZE];

	void sendActionPackets();

	void update();

	void sendPacket(PacketTypes, char *);
};


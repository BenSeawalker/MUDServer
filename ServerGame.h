#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"


class ServerGame
{
public:
	ServerGame();
	~ServerGame();

	void update();

	void ReceiveFromClients();
	void sendActionPackets();

private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	ServerNetwork * network;

	char network_data[MAX_PACKET_SIZE];
};


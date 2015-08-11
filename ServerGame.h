#pragma once
#include "Server.h"


class ServerGame
{
public:
	ServerGame();
	~ServerGame();

	void update();

	void ReceiveFromClients();

private:
	// The ServerNetwork object 
	Server * network;
};


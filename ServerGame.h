#pragma once
#include "Server.h"

#include "GameData.h"
using namespace GameData;

class ServerGame
{
public:
	ServerGame();
	~ServerGame();

	void Update();

	void ReceiveFromClients();

private:
	// The ServerNetwork object 
	Server * network;
};


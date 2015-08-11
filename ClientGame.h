#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "Client.h"

class ClientGame
{
public:
	ClientGame();
	~ClientGame();

	Client * network;

	void sendActionPackets();

	void update();
};


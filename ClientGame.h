#pragma once
#include <winsock2.h>
#include <Windows.h>

#include "Client.h"

#include "Parser.h"

//#include "GameData.h"
//using namespace GameData;

class ClientGame
{
public:
	ClientGame();
	~ClientGame();

	

	void Update();

private:
	Client * network;
	Parser * parser;


	void ReceivePacket();

	//void HandleInput(void *);
};


#include "ServerGame.h"
#include "ClientGame.h"
// used for multi-threading
#include <process.h>

ServerGame * server;
ClientGame * client;
ClientGame * client2;

void serverLoop(void *);
void clientLoop(void);

int main()
{

	// initialize the server
	server = new ServerGame();

	// create thread with arbitrary argument for the run function
	_beginthread(serverLoop, 0, (void*)12);

	// initialize the client 
	client = new ClientGame();
	client2 = new ClientGame();

	clientLoop();
}


void serverLoop(void * arg)
{
	while (true)
	{
		server->update();
	}
}

void clientLoop()
{
	while (true)
	{
		//do game stuff
		client->update();
		client2->update();
	}
}
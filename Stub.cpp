#include "ServerGame.h"
#include "ClientGame.h"

#include "GameData.h"
using namespace GameData;
// used for multi-threading
//#include <process.h>


ServerGame * server;
ClientGame * client;

//void serverLoop(void *);
void ServerLoop();
void ClientLoop();


bool Game_Running = true;
char Server_Address[16] = "127.0.0.1";



int main()
{
	int input;
	bool menu = true;

	

	while (menu)
	{
		cout << "\nMUDServer Example\n"
			<< "\n1. Start Client"
			<< "\n2. Start Server"
			<< "\n3. Change Server Address: " << Server_Address
			<< "\n4. Exit"
			<< "\n\nInput: ";
		GetInput(&input);
		cout << "\n";

		switch (input)
		{
			case 1:
				menu = false;
				client = new ClientGame();
				ClientLoop();
				break;

			case 2:
				menu = false;
				server = new ServerGame();
				ServerLoop();
				break;

			case 3:
				GetInput(Server_Address, 15);
				break;
			case 4:
				menu = false;
				break;

			default:
				cout << "Invalid Input!\n";
				break;
		}
	}
	
	

	// create thread with arbitrary argument for the run function
	//_beginthread(serverLoop, 0, "");

	return 0;
}


void ServerLoop()
{
	while (Game_Running)
		server->Update();
}

void ClientLoop()
{
	while (Game_Running)
		client->Update();
}



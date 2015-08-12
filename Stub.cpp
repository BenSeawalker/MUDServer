#include "ServerGame.h"
#include "ClientGame.h"
// used for multi-threading
//#include <process.h>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;


ServerGame * server;
ClientGame * client;

//void serverLoop(void *);
void ServerLoop();
void ClientLoop();

void GetInput(int * _i);
void GetInput(char * _c);
void GetInput(char * _s, UINT _size);


bool Game_Running = true;
char Server_Address[16] = "127.0.0.1";

int main()
{
	int input;
	bool menu = true;

	while (menu)
	{
		cout << "MUDServer Example\n"
			<< "\n1. Start Client"
			<< "\n2. Start Server"
			<< "\n3. Change Server ip: " << Server_Address
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
		}
	}
	
	

	// create thread with arbitrary argument for the run function
	//_beginthread(serverLoop, 0, "");

	return 0;
}


void ServerLoop()
{
	while (Game_Running)
		server->update();
}

void ClientLoop()
{
	while (Game_Running)
		client->update();
}


void GetInput(int * _i)
{
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

	cin >> *_i;
}

void GetInput(char * _c)
{
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

	cin.get(*_c);
}

void GetInput(char * _s, UINT _size)
{
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();

	cin.getline(_s, _size);
}
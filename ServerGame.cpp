#include "ServerGame.h"


ServerGame::ServerGame()
{
	// set up the server network to listen 
	network = new Server();
}


ServerGame::~ServerGame()
{}


void ServerGame::update()
{
	UINT client_id = network->AcceptNewClient();
	// get new clients
	if (client_id > -1)
		printf("client %d has been connected to the server\n", client_id);

	ReceiveFromClients();
}


void ServerGame::ReceiveFromClients()
{
	Packet packet;

	// go through all clients
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->Sessions.begin(); iter != network->Sessions.end(); iter++)
	{
		int data_length = network->ReceiveData(iter->first, &packet);

		if (data_length)
		{
			switch (packet.type)
			{
				case INIT_CONNECTION:
					printf("server received init packet from client: %s\n", packet.data);
				break;

				case ACTION_EVENT:
					printf("server received action event packet from client: %s\n", packet.data);
				break;

				default:
					printf("error in packet types\n");
				break;
			}
		}
	}
}
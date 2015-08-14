#include "ServerGame.h"


ServerGame::ServerGame()
{
	// set up the server network to listen 
	network = new Server();

	printf("\n\nSERVER STARTED\n\n");
}


ServerGame::~ServerGame()
{}


void ServerGame::Update()
{
	static int c = 0;

	c++;
	if (c > 200000)
	{
		std::map<unsigned int, SOCKET>::iterator iter;

		for (iter = network->Sessions.begin(); iter != network->Sessions.end(); iter++)
		{
			char message[] = "Test";
			NetworkServices::SendPacket(iter->second, ACTION_EVENT, message, strlen(message) + 1);
		}

		c = 0;
	}

	UINT client_id = network->AcceptNewClient();
	// get new clients
	if (client_id > -1)
		printf("client %d has been connected to the server\n", client_id);

	network->HandleDisconnectedClients();

	ReceiveFromClients();
}


void ServerGame::ReceiveFromClients()
{
	// go through all clients
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->Sessions.begin(); iter != network->Sessions.end(); iter++)
	{
		Packet * packet = new Packet();
		int i_result = network->ReceiveData(iter->first, packet);

		if (i_result > 0)
		{
			switch (packet->type)
			{
				case INIT_CONNECTION:
				printf("server received init packet from client %d: %s\n", iter->first, packet->data);
				break;

				case ACTION_EVENT:
				printf("server received action event packet from client %d: %s\n", iter->first, packet->data);
				break;

				default:
					printf("error in packet types\n");
				break;
			}
		}

		delete packet;
	}
}
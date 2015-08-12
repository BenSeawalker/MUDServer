#include "ClientGame.h"


ClientGame::ClientGame()
{
	network = new Client();

	//send init packet
	NetworkServices::SendPacket(network->ConnectSocket, INIT_CONNECTION, "init_data", strlen("init_data")+1);
}


ClientGame::~ClientGame()
{}


void ClientGame::update()
{
	if (!NetworkServices::IsSocketAlive(network->ConnectSocket))
		network->Disconnect();
	else
	{
		Packet * packet = new Packet();
		int i_result = network->ReceivePacket(packet);

		if (i_result > 0)
		{
			switch (packet->type)
			{
				case INIT_CONNECTION:
					memcpy(&network->Client_ID, packet->data, packet->data_size);
					printf("client initialized with ID: %d\n", network->Client_ID);
				break;

				case ACTION_EVENT:
					printf("client %d received action event packet from server\n", network->Client_ID);
				break;

				default:
					printf("error in packet types\n");
				break;
			}
		}

		delete packet;
	}
}
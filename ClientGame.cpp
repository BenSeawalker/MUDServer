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
	Packet packet;
	int data_length = network->ReceivePacket(&packet);

	if (data_length)
	{
		switch (packet.type)
		{
			case CONNECTION_COMPLETE:
				memcpy(&network->Client_ID, packet.data, packet.data_size);
				printf("client %d received init connection packet from server\n", network->Client_ID);
			break;

			case ACTION_EVENT:
				printf("client %d received action event packet from server\n", network->Client_ID);
			break;

			default:
				printf("error in packet types\n");
			break;
		}
	}
}


//void ClientGame::sendActionPackets()
//{
//	// send action packet
//	sendPacket(ACTION_EVENT, "data");
//}
//
//
//void ClientGame::sendPacket(PacketTypes _type, char _data[DEFAULT_BUFLEN])
//{
//	const unsigned int packet_size = sizeof(Packet);
//	char packet_data[packet_size];
//
//	Packet packet;
//	packet.packet_type = _type;
//	memcpy(packet.packet_data, _data, DEFAULT_BUFLEN);
//
//	packet.serialize(packet_data);
//
//	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
//}
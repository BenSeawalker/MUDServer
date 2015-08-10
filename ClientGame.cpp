#include "ClientGame.h"


ClientGame::ClientGame()
{
	network = new ClientNetwork();

	//send init packet
	sendPacket(INIT_CONNECTION, "init_data");
	/*const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;
	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);*/
}


ClientGame::~ClientGame()
{}


void ClientGame::update()
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");

			//sendActionPackets();

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}
}


void ClientGame::sendActionPackets()
{
	// send action packet
	sendPacket(ACTION_EVENT, "data");
}


void ClientGame::sendPacket(PacketTypes _type, char _data[DEFAULT_BUFLEN])
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = _type;
	memcpy(packet.packet_data, _data, DEFAULT_BUFLEN);

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}
#include "NetworkServices.h"

/*****************************************************************************
*	PUBLIC FUNCTIONS
*****************************************************************************/

//	SEND AND RECEIVE PACKETS
//---------------------------------------------------------------------------

	//	Create new packet
	int NetworkServices::SendPacket(SOCKET _socket, PacketTypes _type, char * _data, UINT _dataSize)
	{
		//	the total size of the packet
		UINT packet_size = (PACKET_HEADER_SIZE + _dataSize);

		//	to hold the serialized packet
		char * packet_data = new char[packet_size];

		//	create the packet
		Packet * packet = CreatePacket(_type, _data, _dataSize);

		//serialize and send the data
		packet->serialize(packet_data);
		int i_result = send(_socket, packet_data, packet_size, 0);

		//cleanup
		delete[] packet_data;
		delete packet;

		return i_result;
	}

	//	Send existing packet
	int NetworkServices::SendPacket(SOCKET _socket, Packet * _packet)
	{
		//	the total size of the packet
		UINT packet_size = (PACKET_HEADER_SIZE + _packet->data_size);

		//	to hold the serialized packet
		char * packet_data = new char[packet_size];

		//serialize and send the data
		_packet->serialize(packet_data);
		int i_result = send(_socket, packet_data, packet_size, 0);

		//cleanup
		delete[] packet_data;

		return i_result;
	}


	// receive packet
	int NetworkServices::ReceivePacket(SOCKET _socket, Packet * _packet)
	{
		char * header = new char[PACKET_HEADER_SIZE]();

		int i_result = recv(_socket, header, PACKET_HEADER_SIZE, 0);
		if (i_result)
		{
			_packet->deserialize(header);

			_packet->data = new char[_packet->data_size]();
			i_result = recv(_socket, _packet->data, _packet->data_size, 0);
		}

		return i_result;
	}


//	PACKET MANAGMENT
//---------------------------------------------------------------------------
	Packet * NetworkServices::CreatePacket(PacketTypes _type, char * _data, UINT _dataSize)
	{
		Packet * packet = new Packet();
		packet->type = _type;
		packet->data_size = _dataSize;

		packet->data = new char[_dataSize];
		memcpy(packet->data, _data, _dataSize);

		return packet;
	}

/*****************************************************************************
*	PRIVATE FUNCTIONS
*****************************************************************************/
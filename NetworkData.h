#pragma once
#include <string.h>

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT "2023"

const UINT PACKET_HEADER_SIZE = (sizeof(UINT) * 2);

//typedef unsigned int UINT;

enum PacketTypes
{
	INIT_CONNECTION,
	CONNECTION_COMPLETE,
	ACTION_EVENT,
};

struct Packet
{
	UINT type;
	UINT data_size;
	char * data = nullptr;

	~Packet()
	{
		delete[] data;
	}

	void serialize(char * _data)
	{
		UINT size = sizeof(UINT);
		memcpy(_data, &type, size);						//type
		memcpy(_data + size, &data_size, size);			//data_size
		memcpy(_data + (size * 2), data, data_size);	//data
	}

	void deserialize(char * _header)
	{
		UINT size = sizeof(UINT);
		memcpy(&type, _header, size);				//type
		memcpy(&data_size, _header + size, size);	//data_size
	}
};
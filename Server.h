#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#include <map>

#include "NetworkServices.h"

using std::pair;

class Server
{
public:
	Server();
	~Server();

	// Socket to listen for new connections
	SOCKET ListenSocket;

	// table to keep track of each client's socket
	std::map<UINT, SOCKET> Sessions;

	// accept new connections
	int AcceptNewClient();

	// disconnect client
	bool DisconnectClient(UINT & _clientID);


	// receive incoming data
	int ReceiveData(UINT _clientID, Packet * _packet);

	// send data to all clients
	void SendToAll(PacketTypes _type, char * _data, UINT _dataSize);


private:
	// unique id for each client
	UINT UID;
};


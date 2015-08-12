#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#include <map>

#include "NetworkServices.h"

using std::pair;
using std::map;

class Server
{
public:
	Server();
	~Server();

	// Socket to listen for new connections
	SOCKET ListenSocket;

	// table to keep track of each client's socket
	map<UINT, SOCKET> Sessions;

	// accept new connections
	int AcceptNewClient();

	// check for disconnected clients
	void HandleDisconnectedClients();

	// receive incoming data
	int ReceiveData(UINT _clientID, Packet * _packet);

	// send data to all clients
	void SendToAll(PacketTypes _type, char * _data, UINT _dataSize);


private:
	// disconnect client
	//void DisconnectClient(UINT & _clientID);
};


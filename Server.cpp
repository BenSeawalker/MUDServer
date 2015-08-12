#include "Server.h"

/*****************************************************************************
*	PUBLIC FUNCTIONS
*****************************************************************************/

//	CTOR AND DTOR
//---------------------------------------------------------------------------
Server::Server()
{
	UID = 1;

	// for error checking return values
	int i_result;

	// create WSADATA object
	WSADATA wsaData;

	// our sockets for the server
	ListenSocket = INVALID_SOCKET;



	// address info for the server to listen to
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	i_result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (i_result != 0) {
		printf("WSAStartup failed with error: %d\n", i_result);
		exit(1);
	}

	// set address information
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;    // TCP connection!!!
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	i_result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

	if (i_result != 0) {
		printf("getaddrinfo failed with error: %d\n", i_result);
		WSACleanup();
		exit(1);
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	// Set the mode of the socket to be nonblocking
	u_long iMode = 1;
	i_result = ioctlsocket(ListenSocket, FIONBIO, &iMode);

	if (i_result == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	// Setup the TCP listening socket
	i_result = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

	if (i_result == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	// no longer need address information
	freeaddrinfo(result);

	// start listening for new clients attempting to connect
	i_result = listen(ListenSocket, SOMAXCONN);

	if (i_result == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}

Server::~Server()
{}


//	CLIENT MANAGMENT
//---------------------------------------------------------------------------
	// accept new connections
	int Server::AcceptNewClient()
	{
		// to hold the id of the new client, or -1 if fail
		int ncid = -1;

		// if client waiting, accept the connection and save the socket
		SOCKET client_socket = accept(ListenSocket, NULL, NULL);

		if (client_socket != INVALID_SOCKET)
		{
			ncid = UID++;

			//disable nagle on the client's socket
			char value = 1;
			setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

			// insert new client into session id table
			Sessions.insert(pair<UINT, SOCKET>(ncid, client_socket));

			char * data = NetworkServices::SerializeData(&ncid);
			NetworkServices::SendPacket(client_socket, INIT_CONNECTION, data, sizeof(UINT));
			delete data;
		}

		return ncid;
	}

	bool Server::DisconnectClient(UINT & _clientID)
	{
		bool success = (Sessions.find(_clientID) != Sessions.end());

		if (success)
		{
			SOCKET client_socket = Sessions[_clientID];
			
			printf("Connection to Client %d closed\n", _clientID);
			closesocket(client_socket);
			Sessions.erase(client_socket);
		}

		return success;
	}


// receive incoming data
int Server::ReceiveData(UINT _clientID, Packet * _packet)
{
	// for error checking return values
	int i_result = 0;

	if (Sessions.find(_clientID) != Sessions.end())
	{
		SOCKET currentSocket = Sessions[_clientID];

		i_result = NetworkServices::ReceivePacket(currentSocket, _packet);
		if (i_result == 0)
		{
			DisconnectClient(_clientID);
		}
	}

	return i_result;
}


// send data to all clients
void Server::SendToAll(PacketTypes _type, char * _data, UINT _dataSize)
{
	SOCKET current_socket;
	std::map<unsigned int, SOCKET>::iterator iter;
	int i_result;

	for (iter = Sessions.begin(); iter != Sessions.end(); iter++)
	{
		current_socket = iter->second;

		Packet * packet = NetworkServices::CreatePacket(_type, _data, _dataSize);

		i_result = NetworkServices::SendPacket(current_socket, _type, _data, _dataSize);

		if (i_result == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			DisconnectClient(current_socket);
		}
	}
}


/*****************************************************************************
*	PRIVATE FUNCTIONS
*****************************************************************************/
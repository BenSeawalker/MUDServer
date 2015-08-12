#include "Client.h"


Client::Client()
{
	Client_ID = -1;

	// create WSADATA object
	WSADATA wsaData;

	// socket
	ConnectSocket = INVALID_SOCKET;

	// holds address info for socket to connect to
	struct addrinfo * result = nullptr,
		*ptr = nullptr,
		hints;

	// Initialize Winsock
	int i_result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (i_result != 0) {
		printf("WSAStartup failed with error: %d\n", i_result);
		Disconnect();
	}



	// set address info
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!
	//resolve server address and port 
	i_result = getaddrinfo(Server_Address, DEFAULT_PORT, &hints, &result);

	if (i_result != 0)
	{
		printf("getaddrinfo failed with error: %d\n", i_result);
		Disconnect();
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			Disconnect();
		}

		// Connect to server.
		i_result = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (i_result == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("The server is down... did not connect");
		}
	}



	// no longer need address info for server
	freeaddrinfo(result);



	// if connection failed
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		Disconnect();
	}

	// Set the mode of the socket to be nonblocking
	u_long iMode = 1;

	i_result = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
	if (i_result == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		Disconnect();
	}

	//disable nagle
	char value = 1;
	setsockopt(ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}


Client::~Client()
{}


int Client::ReceivePacket(Packet * _packet)
{
	int i_result = NetworkServices::ReceivePacket(ConnectSocket, _packet);

	if (i_result == 0)
	{
		printf("Connection Lost!\n");
		Disconnect();
	}

	return i_result;
}


void Client::Disconnect()
{
	printf("Connection closed\n");
	closesocket(ConnectSocket);
	WSACleanup();

	Game_Running = false;
}
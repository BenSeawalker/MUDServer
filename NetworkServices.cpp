#include "NetworkServices.h"

int NetworkServices::sendMessage(SOCKET _curSocket, char * _message, int _messageSize)
{
	return send(_curSocket, _message, _messageSize, 0);
}

int NetworkServices::receiveMessage(SOCKET _curSocket, char * _buffer, int _bufferSize)
{
	return recv(_curSocket, _buffer, _bufferSize, 0);
}
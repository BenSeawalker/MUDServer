#include "ClientGame.h"

#include <process.h>
void HandleInput(void *);

#include <conio.h>
#include <stdarg.h>
char input[500] = { '\0' };

void ClearLine();
void PrintMessage(const char * _msg, ...);

ClientGame::ClientGame()
{
	network = new Client();
	parser = new Parser();

	//console.SetCursor(0, 0);
	_beginthread(HandleInput, 0, "");

	//send init packet
	NetworkServices::SendPacket(network->ConnectSocket, INIT_CONNECTION, "init_data", strlen("init_data")+1);
}


ClientGame::~ClientGame()
{}


void ClientGame::Update()
{
	if (!NetworkServices::IsSocketAlive(network->ConnectSocket))
		network->Disconnect();
	else
		ReceivePacket();
}


void ClientGame::ReceivePacket()
{
	Packet * packet = new Packet();
	int i_result = network->ReceivePacket(packet);

	if (i_result > 0)
	{
		switch (packet->type)
		{
			case INIT_CONNECTION:
				memcpy(&network->Client_ID, packet->data, packet->data_size);

				ClearLine();
				cout << "client initialized with ID: " << network->Client_ID;
				cout << "\n\nInput: " << input;

				break;

			case ACTION_EVENT:
				ClearLine();
				cout << "Action_EVENT: " << packet->data;
				cout << "\n\nInput: " << input;
				break;

			default:
				ClearLine();
				cout << "error in packet types\n";
				cout << "\n\nInput: " << input;
				break;
		}
	}

	delete packet;
}


void ClearLine()
{
	for (UINT i = 0; i < WIDTH; i++)
		cout << '\b';
}

void PrintMessage(const char * _msg, ...)
{
	ClearLine();

	va_list args;
	va_start(args, _msg);
	printf(_msg, args);
	printf("\n\nInput: %s", input);
}


void HandleInput(void *)
{
	Parser * parser = new Parser();

	while (true)
	{
		//COORD c_pos = console.cursor;

		//console.SetCursor(0, GameData::HEIGHT - 1);
		input[min(strlen(input), 499)] = _getch();
		
		//GetInput(input, 500);

		//console.SetCursor(c_pos.X, c_pos.Y);

		if (input[strlen(input) - 1] == '\b')
		{
			input[strlen(input) - 1] = '\0';
			input[max(0, strlen(input) - 2)] = '\0';
		}

		if (input[strlen(input) - 1] != '\r')
		{
			ClearLine();
			cout << "Input: " << input;
		}
		else
		{
			input[strlen(input) - 1] = '\0';

			cout << "\n\n";

			Word * sentence;
			UINT num_words = parser->ParseSentence(&sentence, input);

			for (UINT i = 0; i < num_words; i++)
			{
				switch (sentence[i].type)
				{
					case VERB:
						cout << sentence[i].word << " : VERB\n";
						break;
					case NOUN:
						cout << sentence[i].word << " : NOUN\n";
						break;
					case CONJ:
						cout << sentence[i].word << " : CONJ\n";
						break;
					case ARTI:
						cout << sentence[i].word << " : ARTI\n";
						break;
					case NONE:
						cout << sentence[i].word << " : NONE\n";
						break;
				}
			}

			cout << "\n\n";

			for (UINT i = 0; i < 500; i++)
				input[i] = '\0';

			delete[] sentence;
		}
	}
}
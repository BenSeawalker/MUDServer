#pragma once
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <Windows.h>

namespace GameData
{
	const UINT MAX_WORD_LENGTH = 21;

	static const char * Verbs[] = { "get", "take", "pick", "use", "open", "close", "dig", "move", "eat", "drink", "quit" };
	static const char * Nouns[] = { "shovel", "hole", "it" };
	static const char * Conjunctions[] = { "and", "or", "but" };
	static const char * Articles[] = { "with", "the", "a", "an" };

	static const UINT VerbSize = sizeof(Verbs) / sizeof(char*);
	static const UINT NounSize = sizeof(Nouns) / sizeof(char*);
	static const UINT ConjSize = sizeof(Conjunctions) / sizeof(char*);
	static const UINT ArtiSize = sizeof(Articles) / sizeof(char*);

	enum CommandType
	{
		GET,
		USE,
		DIG,
		MOVE,
		LOOK,
		UNDEF
	};

	struct Command
	{
		CommandType atype = UNDEF;
		char action[MAX_WORD_LENGTH];
		char subject[MAX_WORD_LENGTH];
		char object[MAX_WORD_LENGTH];
	};


	enum WordType
	{
		VERB,
		NOUN,
		CONJ,
		ARTI,
		NONE
	};

	struct Word
	{
		WordType type;
		char word[MAX_WORD_LENGTH];
	};


	struct Console
	{
		Console(unsigned width, unsigned height, bool _visible = false, UINT _encoding = 437)
		{
			//ensure that the console is in the correct encoding
			SetConsoleCP(_encoding);
			SetConsoleOutputCP(_encoding);

			//console handle
			hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

			//inner size
			csbi.srWindow.Left = 0;
			csbi.srWindow.Top = 0;
			csbi.srWindow.Right = width - 1;
			csbi.srWindow.Bottom = height - 1;
			SetConsoleWindowInfo(hConOut, TRUE, &csbi.srWindow);


			//window size
			SetConsoleScreenBufferSize(hConOut, { width, height });

			//cursor visibility
			GetConsoleCursorInfo(hConOut, &cinf);
			cinf.bVisible = _visible;
			SetConsoleCursorInfo(hConOut, &cinf);
		}

		~Console()
		{
			SetConsoleTextAttribute(hConOut, csbi.wAttributes);
			SetConsoleScreenBufferSize(hConOut, csbi.dwSize);
			SetConsoleWindowInfo(hConOut, TRUE, &csbi.srWindow);
		}

		void SetColor(WORD color = 0x07)
		{
			SetConsoleTextAttribute(hConOut, color);
		}

		void SetCursor(int _x, int _y)
		{
			cursor.X = _x;
			cursor.Y = _y;
			SetConsoleCursorPosition(hConOut, cursor);
		}

		HANDLE						hConOut;
		CONSOLE_SCREEN_BUFFER_INFO	csbi;
		CONSOLE_CURSOR_INFO			cinf;
		COORD						cursor;
	};


	const int WIDTH = 100;
	const int HEIGHT = 40;
	static Console console(WIDTH, HEIGHT);


	static void PrintMessage(char * message)
	{
		SMALL_RECT consoleWriteArea = console.csbi.srWindow;	//for WriteConsoleOutputA
		CHAR_INFO buffer[WIDTH*HEIGHT] = { '\0' };				//declare empty buffer
	}

	static void GetInput(int * _i)
	{
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();

		cin >> *_i;

		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();
	}

	static void GetInput(char * _c)
	{
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();

		cin.get(*_c);

		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();
	}

	static void GetInput(char * _s, UINT _size)
	{
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();

		cin.getline(_s, _size);

		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();
	}
}


#include "renderer.h"
#include "game.h"

#ifdef _WINDOWS
#include <Windows.h>
#else
#include <iostream>
#endif // _WINDOWS


/*
	unnamed namespace is used to create a local compiling 
	function (not global) that cannot be used outside this file
*/ 
namespace
{
#ifdef _WINDOWS
	void display(char* buffer, int size)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD wr;
		WriteConsoleOutputCharacterA(consoleHandle, buffer, size, { 0, 0 }, &wr);
	}
#else
	void display(char* buffer, int size)
	{
		system("clear");
		std::cout << buffer;
	}
#endif // _WINDOWS
}


#ifdef _WINDOWS
	void renderer::init()
	{
		HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO ci = { };
		GetConsoleCursorInfo(hndl, &ci);
		ci.bVisible = 0;
		SetConsoleCursorInfo(hndl, &ci);
	}
#else
	void renderer::init()
	{

	}
#endif // _WINDOWS



void renderer::draw()
{
	char* buffer = new char[WIDTH * HEIGHT + 1 ];
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		buffer[i] = ' ';
	}
	buffer[WIDTH * HEIGHT] = '\0';

	for (int x = 0; x < game::WIDTH; x++)
	{
		buffer[priv::code(x, 0)] = '#';
		buffer[priv::code(x, game::HEIGHT - 1)] = '#';
	}
	for (int y = 0; y < game::HEIGHT; y++)
	{
		buffer[priv::code(0, y)] = '#';
		buffer[priv::code(game::WIDTH - 1, y)] = '#';
	}

	buffer[priv::code(game::head)] = '1';

	display(buffer, WIDTH * HEIGHT);
	
	delete[] buffer;
}

int renderer::priv::code(int x, int y) { return y * WIDTH + x; }
int renderer::priv::code(Point p) { return p.y * WIDTH + p.x; }
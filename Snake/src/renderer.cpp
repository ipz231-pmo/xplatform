#include "renderer.h"
#include "game.h"

#ifdef _WINDOWS
#include <Windows.h>
#else
#include <iostream>
#endif // _WINDOWS


void renderer::init()
{
#ifdef _WINDOWS
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ci = { };
	GetConsoleCursorInfo(hndl, &ci);
	ci.bVisible = 0;
	SetConsoleCursorInfo(hndl, &ci);
#endif // _WINDOWS
}

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


#ifdef _WINDOWS
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wr;
	WriteConsoleOutputCharacterA(consoleHandle, buffer, WIDTH * HEIGHT, { 0, 0 }, &wr);
#else
	system("clear");
	std::cout << buffer;
#endif 
	
	delete[] buffer;

}

int renderer::priv::code(int x, int y) { return y * WIDTH + x; }
int renderer::priv::code(Point p) { return p.y * WIDTH + p.x; }
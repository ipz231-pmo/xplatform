#include "input.h"

#ifdef _WINDOWS
#include <Windows.h>
#else
#include <conio.h>
#endif // _WINDOWS


#include <game.h>

void input::handle()
{
#ifdef _WINDOWS
	if (GetAsyncKeyState('W') & 0x01) 
	{
		game::dir = Up;
	}
	if (GetAsyncKeyState('A') & 0x01) 
	{
		game::dir = Left;
	}
	if (GetAsyncKeyState('S') & 0x01) 
	{
		game::dir = Down;
	}
	if (GetAsyncKeyState('D') & 0x01) 
	{
		game::dir = Right;
	}
#else
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'w')
		{
			game::dir = Up;
		}
		if (key == 'a')
		{
			game::dir = Left;
		}
		if (key == 's')
		{
			game::dir = Down;
		}
		if (key == 'd')
		{
			game::dir = Right;
		}
	}
#endif
}

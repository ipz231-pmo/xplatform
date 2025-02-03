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
		game::move = true;

		game::left = false;
		game::top = true;
		game::right = false;
		game::down = false;
	}
	if (GetAsyncKeyState('A') & 0x01) 
	{
		game::move = true;

		game::left = true;
		game::top = false;
		game::right = false;
		game::down = false;
	}
	if (GetAsyncKeyState('S') & 0x01) 
	{
		game::move = true;

		game::left = false;
		game::top = false;
		game::right = false;
		game::down = true;
	}
	if (GetAsyncKeyState('D') & 0x01) 
	{
		game::move = true;

		game::left = false;
		game::top = false;
		game::right = true;
		game::down = false;
	}
#else
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'w')
		{
			game::move = true;

			game::left = false;
			game::top = true;
			game::right = false;
			game::down = false;
		}
		if (key == 'a')
		{
			game::move = true;

			game::left = true;
			game::top = false;
			game::right = false;
			game::down = false;
		}
		if (key == 's')
		{
			game::move = true;

			game::left = false;
			game::top = false;
			game::right = false;
			game::down = true;
		}
		if (key == 'd')
		{
			game::move = true;

			game::left = false;
			game::top = false;
			game::right = true;
			game::down = false;
		}
	}
#endif
}

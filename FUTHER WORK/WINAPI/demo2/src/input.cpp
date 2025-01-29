#include "input.h"

void input::handle()
{

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
	

}

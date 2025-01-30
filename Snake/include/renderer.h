#pragma once
#include <Windows.h>
#include <iostream>

#include <typedef.h>
#include <game.h>

namespace renderer
{
	const int WIDTH = 120;
	const int HEIGHT = 30;

	void init();
	void draw();

	namespace priv
	{
		int code(int x, int y);
		int code(Point p);
	}

}
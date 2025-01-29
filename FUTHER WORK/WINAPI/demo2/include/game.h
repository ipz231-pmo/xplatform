#pragma once
#include <typedef.h>

namespace game
{
	const int WIDTH = 20;
	const int HEIGHT = 20;
	const double MOVE_TIME = 2000;

	extern bool left, top, right, down, move;
	extern double moveProcess;

	extern bool gameOver;
	extern Point head;


	void init();
	void update(double deltaTime);
}
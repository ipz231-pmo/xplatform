#pragma once
#include <typedef.h>
#include <vector>

namespace game
{
	const int WIDTH = 20;
	const int HEIGHT = 20;
	const double MOVE_TIME = 2000;

	extern Direction dir;
	extern double moveProcess;

	extern bool gameOver;
	extern Point head;
	extern std::vector<Point> tail;
	extern int score;


	void init();
	void update(double deltaTime);

	namespace priv
	{
		void move();
	}

}
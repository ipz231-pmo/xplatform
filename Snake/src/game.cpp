#include "game.h"

void game::init()
{
	left = false;
	top = false;
	right = false;
	down = false;
	move = false;
	moveProcess = 0;


	gameOver = false;
	head = Point { WIDTH / 2, HEIGHT / 2 };
}

void game::update(double deltaTime)
{
	if (!move) return;
	moveProcess += deltaTime;

	if (moveProcess > MOVE_TIME)
	{
		moveProcess -= MOVE_TIME;
		if (top) head.y--;
		if (left) head.x--;
		if (down) head.y++;
		if (right) head.x++;

		if (head.x < 1) head.x = 1;
		if (head.y < 1) head.y = 1;
		if (head.x > WIDTH-2) head.x = WIDTH - 2;
		if (head.y > HEIGHT-2) head.y = HEIGHT - 2;
	}

}

bool game::left, game::top, game::right, game::down, game::move;
double game::moveProcess;


Point game::head;
bool game::gameOver;

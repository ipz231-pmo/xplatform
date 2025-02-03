#include "game.h"

void game::init()
{
	dir = None;
	moveProcess = 0;


	gameOver = false;
	head = Point { WIDTH / 2, HEIGHT / 2 };
}

void game::update(double deltaTime)
{
	if (dir == None) return;
	if (gameOver) return;
	moveProcess += deltaTime;

	priv::move();

}

void game::priv::move()
{
	if (moveProcess > MOVE_TIME) return;
	
	moveProcess -= MOVE_TIME;
	if (dir == Up) head.y--;
	if (dir == Left) head.x--;
	if (dir == Down) head.y++;
	if (dir == Right) head.x++;

	if (head.x < 1) head.x = 1;
	if (head.y < 1) head.y = 1;
	if (head.x > WIDTH - 2) head.x = WIDTH - 2;
	if (head.y > HEIGHT - 2) head.y = HEIGHT - 2;
}

Direction game::dir;
double game::moveProcess;


Point game::head;
bool game::gameOver;
std::vector<Point> game::tail;
int game::score;


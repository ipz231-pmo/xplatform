
#include "game.h"
#include "renderer.h"
#include "input.h"

#include <ctime>

int main(int argc, char* argv[])
{
	game::init();
	renderer::init();


	clock_t start = clock();


	while (!game::gameOver)
	{
		clock_t end = clock();
		double deltaTime = (double)(end - start) / CLOCKS_PER_SEC;

		input::handle();
		game::update(deltaTime);
		renderer::draw();
	}

}
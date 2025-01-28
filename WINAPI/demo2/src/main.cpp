#include <Windows.h>

#include "game.h"
#include "renderer.h"
#include "input.h"



int main(int argc, char* argv[])
{
	game::init();
	renderer::init();


	clock_t start = clock();

	while (1)
	{
		clock_t end = clock();
		double deltaTime = (double)(end - start) / CLOCKS_PER_SEC;


		input::handle();
		game::update(deltaTime);
		renderer::draw();
	}

}
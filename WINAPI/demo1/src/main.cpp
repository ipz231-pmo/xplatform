#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <glad/glad.h>

#include <Windows.h>

#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>

#include "main.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include <glad/glad.h>
#include <glh/Shader.hpp>


float vertices[] =
{
	-0.5, -0.5, 0,
	0.5, -0.5, 0,
	0.5, 0.5, 0
};

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	
	


	App::hInstance = hInstance;


	if (!Window::createWindow())
	{
		return -1;
	}


	freopen("test.txt", "w", stderr);
	Shader shader(App::SHADERS_DIRECTION + "1.vert", App::SHADERS_DIRECTION + "1.frag");
	fclose(stderr);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader Input Params
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	MSG msg = { };


	while (!Window::done)
	{
		Time::calcDeltaTime();

		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				Window::done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		shader.bind();
		shader.setVec3("Color", glm::vec3(1.0, 1.0, 1.0));

		// Draw here
		glClearColor(0.5, 0, 0, 1.0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(Window::hdc);
	}
	return 0;

}

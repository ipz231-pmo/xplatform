#include "main.hpp"

// Funcion declarations
void proccessInput();
void update();
void render();



void proccessInput()
{
	if (firstMouseMove) {
		firstMouseMove = false;
		cursorLastPosX = sf::Mouse::getPosition(*wnd).x;
		cursorLastPosY = sf::Mouse::getPosition(*wnd).y;
	}

	cursorDx = cursorLastPosX - sf::Mouse::getPosition(*wnd).x;
	cursorDy = cursorLastPosY - sf::Mouse::getPosition(*wnd).y;
	cursorDx *= -MOUSE_SENSETIVITY;
	cursorDy *= MOUSE_SENSETIVITY;
	cursorLastPosX = sf::Mouse::getPosition(*wnd).x;
	cursorLastPosY = sf::Mouse::getPosition(*wnd).y;

	sf::Event e;
	while (wnd->pollEvent(e))
	{
		if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape))
		{
			wnd->close();
		}
		if (e.type == sf::Event::KeyPressed) {
			keysPressed[e.key.code] = true;

			if (e.key.code == sf::Keyboard::Z)
				selectedCube++;
			if (e.key.code == sf::Keyboard::X)
				selectedCube--;

			if (selectedCube >= cubesPosition.size()) selectedCube = 0;
			if (selectedCube < 0) selectedCube = cubesPosition.size() - 1;
		}
		if (e.type == sf::Event::KeyReleased) {
			keysPressed[e.key.code] = false;
		}
	}

}

void update()
{
	// Camera Movement
	yaw += cursorDx;
	pitch += cursorDy;
	if (pitch > 1.56f)
		pitch = 1.56f;
	if (pitch < -1.56f)
		pitch = -1.56f;
	glm::vec3 frontDir;
	frontDir.x = cos(yaw) * cos(pitch);
	frontDir.y = sin(pitch);
	frontDir.z = sin(yaw) * cos(pitch);

	// Camera Movement
	float dx = 0, dy = 0;
	if (keysPressed[sf::Keyboard::W])
		dy += 1;
	if (keysPressed[sf::Keyboard::S])
		dy -= 1;
	if (keysPressed[sf::Keyboard::A])
		dx -= 1;
	if (keysPressed[sf::Keyboard::D])
		dx += 1;
	cameraPos += frontDir * MOVE_SPEED * dy * deltaTime;
	cameraPos += glm::cross(frontDir, glm::vec3(0.0f, 0.1f, 0.0f)) * MOVE_SPEED * dx * deltaTime;

	// Mirror Camera
}

void render()
{
	glm::vec3 frontDir;
	frontDir.x = cos(yaw) * cos(pitch);
	frontDir.y = sin(pitch);
	frontDir.z = sin(yaw) * cos(pitch);

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + frontDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)wnd->getSize().x / wnd->getSize().y, 0.1f, 100.0f);

	unlitShader->bind();
	unlitShader->setMat4("view", view);
	unlitShader->setMat4("proj", proj);
	unlitShader->setInt("tex0", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	unlitShader->unbind();

	glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	glBindVertexArray(VAO);


	wnd->display();
}













// Graphics vars
float cubeVertices[] = {
	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	 // Bottom face
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	  0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	 // Top face
	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
	  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};
Shader* unlitShader;
unsigned int VAO;
unsigned int VBO;
unsigned int dirtTexture;
// Camera
float yaw = 3.1415, pitch;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraDir;
// Mirror
glm::vec3 MirrorPos;
// Cursor 
float cursorDx, cursorDy, cursorLastPosX, cursorLastPosY;
bool firstMouseMove = 1;
// System vars
sf::Window* wnd;
sf::Clock* timer;
float deltaTime;
std::map<sf::Keyboard::Key, bool> keysPressed;
#include "main.hpp"


void proccessInput();
void update();
void render();


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

int main() {
	for (int x = 0; x < 10; x++)
	{
		for (int z = 0; z < 10; z++)
		{
			cubesPosition.push_back(glm::vec3(x, 0, z));
		}
	}
	for (int i = sf::Keyboard::A; i < sf::Keyboard::KeyCount; i++)
	{
		keysPressed[static_cast<sf::Keyboard::Key>(i)] = false;
	}

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 6;


	wnd = new sf::Window(sf::VideoMode(800, 600), "OutLine text", 7U, contextSettings);
	timer = new sf::Clock();

	gladLoadGL();

	SColorShader = new Shader(SHADERS_DIR + "SColortShader.vert", SHADERS_DIR + "SColortShader.frag");
	unlitShader = new Shader(SHADERS_DIR + "unlitShader.vert", SHADERS_DIR + "unlitShader.frag");
	
	wnd->setActive();
	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	{
		int width, height, chanels;
		unsigned char* data = stbi_load((TEXTURES_DIR + "dirt.png").c_str(), &width, &height, &chanels, 0);
		if (!data) {
			std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_DIRT_TEXTURE\n";
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	// Shader Input Params
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (wnd->isOpen())
	{
		deltaTime = timer->restart().asMilliseconds();

		proccessInput();
		update();
		render();
	}

}

void proccessInput() {

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
			if (selectedCube < 0) selectedCube = cubesPosition.size()-1;
		}
		if (e.type == sf::Event::KeyReleased) {
			keysPressed[e.key.code] = false;
		}
	}
}

void render()
{
	glm::vec3 frontDir = { };
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

	SColorShader->bind();
	SColorShader->setMat4("view", view);
	SColorShader->setMat4("proj", proj);
	SColorShader->setVec3("Color", glm::vec3(0.0f, 0.0f, 0.0f));
	SColorShader->unbind();



	glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	

	glBindVertexArray(VAO);

	for (int i = 0; i < cubesPosition.size(); i++)
	{

		glm::vec3 cPos = cubesPosition[i];

		if (selectedCube == i)
			continue;

		glClear(GL_STENCIL_BUFFER_BIT);
		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		unlitShader->bind();
		glm::mat4 model(1.0f);
		model = glm::translate(model, cPos);
		unlitShader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	}

	glm::vec3 cPos = cubesPosition[selectedCube];
	glStencilMask(0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	unlitShader->bind();




	glm::mat4 model;

	model = glm::translate({1.0f}, cPos);
	model = glm::scale(model, glm::vec3(1.0f - BORDER_THICKNESS, 1.0f - BORDER_THICKNESS, 1.0f));
	unlitShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 12);


	model = glm::translate({ 1.0f }, cPos);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f - BORDER_THICKNESS, 1.0f - BORDER_THICKNESS));
	unlitShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 12, 12);

	model = glm::translate({ 1.0f }, cPos);
	model = glm::scale(model, glm::vec3(1.0f - BORDER_THICKNESS, 1, 1.0f - BORDER_THICKNESS));
	unlitShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 24, 12);

	glStencilMask(0x00);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	SColorShader->bind();
	SColorShader->setMat4("model", glm::translate(glm::mat4(1.0f), cPos));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glClear(GL_STENCIL_BUFFER_BIT);



	glStencilMask(0xFF);

	wnd->display();
}

void update()
{
	yaw += cursorDx;
	pitch += cursorDy;
	if (pitch > 1.56f)
		pitch = 1.56f;
	if (pitch < -1.56f)
		pitch = -1.56f;

	float dx = 0, dy = 0;

	if (keysPressed[sf::Keyboard::W])
		dy += 1;
	if (keysPressed[sf::Keyboard::S])
		dy -= 1;
	if (keysPressed[sf::Keyboard::A])
		dx -= 1;
	if (keysPressed[sf::Keyboard::D])
		dx += 1;

	glm::vec3 frontDir;
	frontDir.x = cos(yaw) * cos(pitch);
	frontDir.y = sin(pitch);
	frontDir.z = sin(yaw) * cos(pitch);
	
	cameraPos += frontDir * MOVE_SPEED * dy * deltaTime;
	cameraPos += glm::cross(frontDir, glm::vec3(0.0f, 0.1f, 0.0f)) * MOVE_SPEED * dx * deltaTime;
}

sf::Window* wnd;
sf::Clock* timer;

Shader* unlitShader;
Shader* SColorShader;

unsigned int VAO;
unsigned int VBO;

std::map<sf::Keyboard::Key, bool> keysPressed;

float yaw = 3.1415, pitch;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);

float cursorDx, cursorDy, cursorLastPosX, cursorLastPosY;
bool firstMouseMove = 1;

float deltaTime;
unsigned int texture;
std::vector<glm::vec3> cubesPosition;
int selectedCube;
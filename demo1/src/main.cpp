// SFMLLearn.cpp : Defines the entry point for the application.
//

#include "main.hpp"

void init() {
	sf::ContextSettings context;
	context.majorVersion = 3;
	context.minorVersion = 3;
	context.depthBits = 24;

	wnd = new sf::RenderWindow(sf::VideoMode(800, 600), "WND Title", 7U, context);
	gladLoadGL();
	unlitShader = new Shader(SHADERS_DIR + "/unlitShader.vert", SHADERS_DIR + "/unlitShader.frag");
	timer = new sf::Clock();
	camera = new engine::Camera();
	camera->translate(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->rotate(glm::radians(270.0f), 0);
	chunk = new engine::Chunk();

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			chunk->setBlock(x, 0, z, new engine::Block(engine::Block::grass));
			if(x % 2 == 0)
				chunk->setBlock(x, 0, z, new engine::Block(engine::Block::dirt));
		}
	}

	chunk->setBlock(8, 8, 10, new engine::Block(engine::Block::grass));

	engine::Block::unlitShader = unlitShader;
	engine::Block::unlitVAO = &unlitVAO;
	engine::Chunk::unlitShader = unlitShader;
	for (int key = 0; key < sf::Keyboard::Key::KeyCount; key++)
	{
		keysPressed[static_cast<sf::Keyboard::Key>(key)] = false;
	}

	//std::cout << "Dirt" textures["dirt"] << "\n";


	initGL();
	initTextures();

	engine::Block::BACK_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];
	engine::Block::FRONT_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];
	engine::Block::LEFT_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];
	engine::Block::RIGHT_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];
	engine::Block::TOP_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];
	engine::Block::BOTTOM_SIDE_TEXTURES[engine::Block::dirt] = textures["dirt"];

	engine::Block::BACK_SIDE_TEXTURES[engine::Block::grass] = textures["grass_side"];
	engine::Block::FRONT_SIDE_TEXTURES[engine::Block::grass] = textures["grass_side"];
	engine::Block::LEFT_SIDE_TEXTURES[engine::Block::grass] = textures["grass_side"];
	engine::Block::RIGHT_SIDE_TEXTURES[engine::Block::grass] = textures["grass_side"];

	engine::Block::TOP_SIDE_TEXTURES[engine::Block::grass] = textures["grass_top"];
	engine::Block::BOTTOM_SIDE_TEXTURES[engine::Block::grass] = textures["dirt"];
}

void initGL()
{
	stbi_set_flip_vertically_on_load(1);

	wnd->setActive();
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &unlitVAO);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(unlitVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void initTextures()
{
	textures["dirt"] = 0;
	glGenTextures(1, &textures["dirt"]);
	glBindTexture(GL_TEXTURE_2D, textures["dirt"]);
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

	textures["grass_side"] = 0;
	glGenTextures(1, &textures["grass_side"]);
	glBindTexture(GL_TEXTURE_2D, textures["grass_side"]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	{
		int width, height, chanels;
		unsigned char* data = stbi_load((TEXTURES_DIR + "grass_side.png").c_str(), &width, &height, &chanels, 0);
		if (!data) {
			std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_DIRT_TEXTURE\n";
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	textures["grass_top"] = 0;
	glGenTextures(1, &textures["grass_top"]);
	glBindTexture(GL_TEXTURE_2D, textures["grass_top"]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	{
		int width, height, chanels;
		unsigned char* data = stbi_load((TEXTURES_DIR + "grass_top.png").c_str(), &width, &height, &chanels, 0);
		if (!data) {
			std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_DIRT_TEXTURE\n";
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
}

void loop() {
	while (wnd->isOpen())
	{
		deltaTime = timer->getElapsedTime().asMilliseconds();
		timer->restart();
		
		cursorMoveOffsetX = 0;
		cursorMoveOffsetY = 0;

		sf::Event e;
		while (wnd->pollEvent(e))
		{
			if (e.type == sf::Event::Closed) wnd->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
				camera->rotate(0, glm::radians(5.0f) * deltaTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
				camera->rotate(0, glm::radians(-5.0f) * deltaTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
				camera->rotate(glm::radians(-5.0f) * deltaTime, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
				camera->rotate(glm::radians(5.0f) * deltaTime, 0);
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				keysPressed[sf::Keyboard::W] = true;
			else
				keysPressed[sf::Keyboard::W] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				keysPressed[sf::Keyboard::S] = true;
			else
				keysPressed[sf::Keyboard::S] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				keysPressed[sf::Keyboard::A] = true;
			else
				keysPressed[sf::Keyboard::A] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				keysPressed[sf::Keyboard::D] = true;
			else
				keysPressed[sf::Keyboard::D] = false;
			
			if (e.type == sf::Event::MouseMoved)
			{
				if (firstMouseMove) {
					firstMouseMove = false;
					lastCursorX = e.mouseMove.x;
					lastCursorY = e.mouseMove.y;
				}

				cursorMoveOffsetX = e.mouseMove.x - lastCursorX;
				cursorMoveOffsetY = -e.mouseMove.y + lastCursorY;

				lastCursorX = e.mouseMove.x;
				lastCursorY = e.mouseMove.y;
			}

		}

		if(keysPressed[sf::Keyboard::W])
			camera->translate(camera->getDirection() * 0.01f * deltaTime);
		if (keysPressed[sf::Keyboard::S])
			camera->translate(camera->getDirection() * -0.01f * deltaTime);
		if (keysPressed[sf::Keyboard::A])
			camera->translate(glm::cross(glm::vec3(0, 1, 0), camera->getDirection()) * 0.01f * deltaTime);
		if (keysPressed[sf::Keyboard::D])
			camera->translate(glm::cross(glm::vec3(0, 1, 0), camera->getDirection()) * -0.01f * deltaTime);
		
		camera->rotate(cursorMoveOffsetX * MOUSE_SENSETIVITY, cursorMoveOffsetY * MOUSE_SENSETIVITY);

		render();
	}
}

void render()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);

	unlitShader->bind();
	unlitShader->setMat4("view", camera->getViewMatrix());
	unlitShader->setMat4("proj", camera->getProjectionMatrix());
	unlitShader->setInt("tex0", 0);
	glActiveTexture(GL_TEXTURE0);

	chunk->render(model);

	wnd->display();
}


int main()
{
	init();
	loop();

	return 0;
}


sf::RenderWindow* wnd;
Shader* unlitShader;
sf::Clock* timer;
engine::Camera* camera;
engine::Chunk* chunk;
std::map<std::string, unsigned int> textures;
std::map<sf::Keyboard::Key, bool> keysPressed;
float deltaTime;
int lastCursorX;
int lastCursorY;
bool firstMouseMove = true;
unsigned int unlitVAO;
unsigned int cubeVBO;
int cursorMoveOffsetX;
int cursorMoveOffsetY;

float cubeVertices[288] = {
	// positions            // normals             // texture coords
	// backface
	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     1.0f, 0.0f, // left bottom    -> right bottom
	 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     0.0f, 0.0f, // right bottom   -> left bottom
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     0.0f, 1.0f, // right up		 -> left top
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     0.0f, 1.0f, // right top		 -> left top
	-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     1.0f, 1.0f, // left top		 -> right top
	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,     1.0f, 0.0f, // left bottom	 -> right bottom

	// frontface
	-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,      0.0f, 0.0f,

	// leftface
	-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,      1.0f, 1.0f,

	// rightface
	 0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,

	 // downface
	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,     0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,     1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,     1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,     0.0f, 1.0f,

	// topface
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,      1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,      0.0f, 1.0f
};
#pragma once
#include "glad/glad.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi/stb_image.h"

#include "Camera.hpp"
#include "Block.hpp"
#include "Chunk.hpp"
#include "World.hpp"

#include <glh/Shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


extern sf::RenderWindow* wnd;
extern Shader* unlitShader;
extern sf::Clock* timer;
extern Camera* camera;
extern Chunk* chunk;

extern float deltaTime;

const std::string ASSETS_DIR = "../assets/";
const std::string SHADERS_DIR = ASSETS_DIR + "shaders/";
const std::string TEXTURES_DIR = ASSETS_DIR + "textures/";

const float MOUSE_SENSETIVITY = 0.1f;

extern unsigned int unlitVAO;
extern unsigned int cubeVBO;
extern float cubeVertices[288];

extern float cursorDx;
extern float cursorDy;

extern std::map<std::string, unsigned int> textures;
extern std::map<sf::Keyboard::Key, bool> keysPressed;

void init();
void loop();
void render();
void proccessInput();
void initGL();
void initTextures();
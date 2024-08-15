#include "glad/glad.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi/stb_image.h"

#include <glh/Shader.hpp>
#include "Engine/Engine.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


extern sf::RenderWindow* wnd;
extern Shader* unlitShader;
extern sf::Clock* timer;
extern engine::Camera* camera;
extern engine::Chunk* chunk;

extern float deltaTime;

const std::string ASSETS_DIR = "../assets/";
const std::string SHADERS_DIR = ASSETS_DIR + "shaders/";
const std::string TEXTURES_DIR = ASSETS_DIR + "textures/";

const float MOUSE_SENSETIVITY = 0.01f;

extern unsigned int unlitVAO;
extern unsigned int cubeVBO;
extern float cubeVertices[288];

extern int lastCursorX;
extern int lastCursorY;
extern bool firstMouseMove;
extern int cursorMoveOffsetX;
extern int cursorMoveOffsetY;

extern std::map<std::string, unsigned int> textures;
extern std::map<sf::Keyboard::Key, bool> keysPressed;

void init();
void loop();
void render();

void initGL();
void initTextures();
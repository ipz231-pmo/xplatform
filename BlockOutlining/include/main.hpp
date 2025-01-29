#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>



#include <Shader.hpp>
#include <Texture2D.hpp>

const std::string PROJECT_DIR = "../";
const std::string SHADERS_DIR = PROJECT_DIR + "shaders/";
const std::string TEXTURES_DIR = PROJECT_DIR + "textures/";

const float MOUSE_SENSETIVITY = 0.01f;
const float MOVE_SPEED = 0.05f;
const float BORDER_THICKNESS = 0.04f;

extern sf::Window* wnd;
extern sf::Clock* timer;

extern Shader* unlitShader;
extern Shader* SColorShader;

extern unsigned int VAO;
extern unsigned int VBO;

extern std::map<sf::Keyboard::Key, bool> keysPressed;

// Camera
extern float yaw, pitch;
extern glm::vec3 cameraPos;

// Cursor 
extern float cursorDx, cursorDy, cursorLastPosX, cursorLastPosY;
extern bool firstMouseMove;

extern float deltaTime;

extern Texture2D* texture;

extern std::vector<glm::vec3> cubesPosition;

extern int selectedCube;
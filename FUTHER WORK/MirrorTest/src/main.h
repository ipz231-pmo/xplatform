#include <glh/Shader.hpp>
#include <SFML/Graphics.hpp>
#include <stbi/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern sf::Window* wnd;
extern sf::Clock* timer;

extern Shader* unlitShader;

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

extern unsigned int dirtTexture;
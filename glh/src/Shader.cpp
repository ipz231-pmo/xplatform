#include "glh/Shader.hpp"

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
	std::ifstream vsStream;
	std::ifstream fsStream;
	vsStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream vsBuff;
	std::stringstream fsBuff;
	vsStream.open(vertexFile);
	fsStream.open(fragmentFile);
	vsBuff << vsStream.rdbuf();
	fsBuff << fsStream.rdbuf();
	std::string vsStr = vsBuff.str();
	std::string fsStr = fsBuff.str();
	const char* vsCStr = vsStr.c_str();
	const char* fsCStr = fsStr.c_str();

	int success;
	char buffer[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsCStr, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_VERTEX_SHADER\n";
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsCStr, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_FRAGMENT_SHADER\n";
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER_PROGRAM::FAILED_TO_LINK_SHADERS\n";
		glGetProgramInfoLog(ID, 512, 0, buffer);
		std::cout << buffer << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::unbind() {
	glUseProgram(0);
}


void Shader::setInt(std::string uniformName, int value) {
	glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
}
void Shader::setFloat(std::string uniformName, float value) {
	glUniform1f(glGetUniformLocation(ID, uniformName.c_str()), value);
}
void Shader::setVec3(std::string uniformName, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(ID, uniformName.c_str()), x, y, z);
}
void Shader::setVec3(std::string uniformName, const glm::vec3& vec) {
	glUniform3f(glGetUniformLocation(ID, uniformName.c_str()), vec.x, vec.y, vec.z);
}
void Shader::setMat4(std::string uniformName, const glm::mat4& transform) {
	glUniformMatrix4fv(glGetUniformLocation(ID, uniformName.c_str()), 1, GL_FALSE, &transform[0][0]);
}

void Shader::bind() {
	glUseProgram(ID);
}
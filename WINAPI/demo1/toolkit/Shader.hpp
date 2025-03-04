#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


class Shader
{
public:
	Shader(std::string vertexFile, std::string fragmentFile);
	unsigned int ID;
	void bind();
	void unbind();
	void setInt(std::string uniformName, int value);
	void setFloat(std::string uniformName, float value);
	void setVec3(std::string uniformName, float x, float y, float z);
	void setVec3(std::string uniformName, const glm::vec3& vec);
	void setMat4(std::string uniformName, const glm::mat4& mat);
};


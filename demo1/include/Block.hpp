#pragma once
#include <glad/glad.h>
#include <map>
#include <glh/Shader.hpp>


class Block
{
public:
	enum Type
	{
		grass,
		dirt
	};
private:
	Type ID;
public:
	Block(Type id);
	void render();
	int getID();

	static unsigned int* unlitVAO;
	static Shader* unlitShader;


};
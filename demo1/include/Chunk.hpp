#pragma once
#include "Block.hpp"
#include <glh/Shader.hpp>

class Chunk
{
private:
	Block *blocks [16][256][16];
public:
	Chunk();
	void render(glm::mat4 model);
	void setBlock(int x, int y, int z, Block* block);
	Block* getBlock(int x, int y, int z);

	static Shader* unlitShader;
};
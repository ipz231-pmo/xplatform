#include <Engine/Chunk.hpp>

engine::Chunk::Chunk()
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				blocks[x][y][z] = nullptr;
			}
		}
	}
}

void engine::Chunk::render(glm::mat4 model)
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				engine::Block* block = blocks[x][y][z];
				if (!block) continue;
				unlitShader->bind();
				model = glm::translate(model, glm::vec3(x, y, z));
				unlitShader->setMat4("model", model);
				block->render();
				model = glm::translate(model, glm::vec3(-x, -y, -z));
			}
		}
	}
}

void engine::Chunk::setBlock(int x, int y, int z, Block* block) {
	if (x >= 16 || x < 0 || y >= 256 || y < 0 || z >= 16 || z < 0) {
		throw "error::bad_pos";
	}
	blocks[x][y][z] = block;
}
engine::Block* engine::Chunk::getBlock(int x, int y, int z) {
	if (x >= 16 || x < 0 || y >= 256 || y < 0 || z >= 16 || z < 0) {
		throw "error::bad_pos";
	}
	return blocks[x][y][z];
}

Shader* engine::Chunk::unlitShader;
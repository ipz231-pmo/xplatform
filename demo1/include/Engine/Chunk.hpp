#pragma once
#include <Engine/Engine.hpp>

namespace engine {
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
}
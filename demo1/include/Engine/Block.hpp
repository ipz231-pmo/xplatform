#pragma once
#include <glad/glad.h>
#include <map>
#include <glh/Shader.hpp>

namespace engine
{
	class Block
	{
	public:
		enum BlockType
		{
			grass,
			dirt
		};
	private:
		BlockType ID;
	public:
		Block(BlockType id);
		void render();
		int getID();

		static unsigned int* unlitVAO;
		static Shader* unlitShader;

		

		static std::map<BlockType, unsigned int>   LEFT_SIDE_TEXTURES;
		static std::map<BlockType, unsigned int>  RIGHT_SIDE_TEXTURES;
		static std::map<BlockType, unsigned int>  FRONT_SIDE_TEXTURES;
		static std::map<BlockType, unsigned int>   BACK_SIDE_TEXTURES;
		static std::map<BlockType, unsigned int> BOTTOM_SIDE_TEXTURES;
		static std::map<BlockType, unsigned int>    TOP_SIDE_TEXTURES;
	};
}
#include "Engine/Block.hpp"

engine::Block::Block(BlockType id) {
	ID = id;
}


void engine::Block::render() {
	unlitShader->bind();
	glBindVertexArray(*unlitVAO);

	glBindTexture(GL_TEXTURE_2D, BACK_SIDE_TEXTURES[ID]);
	std::cout << BACK_SIDE_TEXTURES[ID] << " ";
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, FRONT_SIDE_TEXTURES[ID]);
	std::cout << FRONT_SIDE_TEXTURES[ID] << " ";
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, LEFT_SIDE_TEXTURES[ID]);
	std::cout << LEFT_SIDE_TEXTURES[ID] << " ";
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, RIGHT_SIDE_TEXTURES[ID]);
	std::cout << RIGHT_SIDE_TEXTURES[ID] << " ";
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, BOTTOM_SIDE_TEXTURES[ID]);
	std::cout << BOTTOM_SIDE_TEXTURES[ID] << " ";
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, TOP_SIDE_TEXTURES[ID]);
	std::cout << TOP_SIDE_TEXTURES[ID] << "\n";
	glDrawArrays(GL_TRIANGLES, 30, 6);
	unlitShader->unbind();
}

int engine::Block::getID() {
	return ID;
}


std::map<engine::Block::BlockType, unsigned int> engine::Block::LEFT_SIDE_TEXTURES;
std::map<engine::Block::BlockType, unsigned int> engine::Block::RIGHT_SIDE_TEXTURES;
std::map<engine::Block::BlockType, unsigned int> engine::Block::FRONT_SIDE_TEXTURES;
std::map<engine::Block::BlockType, unsigned int> engine::Block::BACK_SIDE_TEXTURES;
std::map<engine::Block::BlockType, unsigned int> engine::Block::BOTTOM_SIDE_TEXTURES;
std::map<engine::Block::BlockType, unsigned int> engine::Block::TOP_SIDE_TEXTURES;

unsigned int* engine::Block::unlitVAO;
Shader* engine::Block::unlitShader;
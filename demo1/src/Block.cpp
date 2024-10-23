#include "Block.hpp"

Block::Block(Type id) {
	ID = id;
}

void Block::render() {
	unlitShader->bind();
	glBindVertexArray(*unlitVAO);

	glBindTexture(GL_TEXTURE_2D, BACK_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, FRONT_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, LEFT_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, RIGHT_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, BOTTOM_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, TOP_SIDE_TEXTURES[ID]);
	glDrawArrays(GL_TRIANGLES, 30, 6);
	unlitShader->unbind();
}

int Block::getID() {
	return ID;
}


std::map<Block::Type, unsigned int> Block::LEFT_SIDE_TEXTURES;
std::map<Block::Type, unsigned int> Block::RIGHT_SIDE_TEXTURES;
std::map<Block::Type, unsigned int> Block::FRONT_SIDE_TEXTURES;
std::map<Block::Type, unsigned int> Block::BACK_SIDE_TEXTURES;
std::map<Block::Type, unsigned int> Block::BOTTOM_SIDE_TEXTURES;
std::map<Block::Type, unsigned int> Block::TOP_SIDE_TEXTURES;

unsigned int* Block::unlitVAO;
Shader* Block::unlitShader;
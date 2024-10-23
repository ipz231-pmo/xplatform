#pragma once

#include <map>

#include "Chunk.hpp"

class World
{
public:
	World(int seed);
	void generateChunk(int x, int y);
	Chunk* getChunk(int x, int y);
	void setRenderDist(int r);
private:
	Chunk*** m_chunks;
	int m_seed;
	int m_renderDist;
};
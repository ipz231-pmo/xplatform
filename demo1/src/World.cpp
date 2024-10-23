#include "World.hpp"

World::World(int seed) 
	: 
	m_seed(seed),
	m_renderDist(4),
	m_chunks(nullptr)
{
	m_chunks = new Chunk * *[m_renderDist * 2 + 1];
	for (int x = 0; x < m_renderDist*2+1; x++)
	{
		m_chunks[x] = new Chunk * [m_renderDist * 2 + 1];
		for (int z = 0; z < m_renderDist * 2 + 1; z++)
		{
			generateChunk(x, z);
		}
	}

}

void World::generateChunk(int x, int z) {

}
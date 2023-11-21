#pragma once

#include "glm/glm.hpp"
#include "Chunk.h"
#include <map>

class World
{
public:
	World();
	~World();

	void Render(Shader* shader);

private:
	std::map<glm::vec2, Chunk*> chunks;
	//std::vector<Chunk> chunks;

	int numChunksWidth = 20;
	int numChunksHeight = 11;
};

World::World()
{
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			chunks[glm::vec2(x, y)] = new Chunk();

		}
	}
}

World::~World()
{
}
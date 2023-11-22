#include "World.h"

World::World()
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			chunks[glm::vec2(x, y)] = new Chunk(x * 64, y * 64);;
		}
	}
}

World::~World()
{
	for (auto& chunk : chunks)
	{
		delete chunk.second;
	}
}

void World::Render(Shader* shader)
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			Chunk* chunk = chunks[glm::vec2(x, y)];

			if(chunk != nullptr)
			{
				chunk->DrawMesh(shader);
			}

			//glm::vec2 key(x, y);
			//auto it = chunks.find(key);
			//if (it != chunks.end())
			//{
			//	Chunk* chunk = it->second;
			//	chunk->CreateMesh();
			//	chunk->DrawMesh(shader);
			//}
			//else
			//{
			//	// Handle the case where the key is not in the map...
			//}
		}
	}
}
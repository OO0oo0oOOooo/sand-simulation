#include "World.h"

World::World()
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			chunks[glm::vec2(x, y)] = new Chunk(x * 64, y * 64);
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

void World::UpdateChunks()
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			Chunk* chunk = chunks[glm::vec2(x, y)];

			/* && chunk->dirty*/
			if (chunk != nullptr)
			{
				UpdateCells(chunk);
			}
		}
	}
}


void World::UpdateCells(Chunk* chunk)
{
	// Update inside the chunk or Update outside the chunk then pass the data back in?


	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			if (chunk->GetCell(x, y).Id == ParticleSand.Id)
			{
				if (y % 64 == 0)
				{
					// This currently replaces whatever cell is at the top of the next chunk. I want to test to see if i can move there
					chunk->SetCell(x, y, ParticleAir);

					glm::vec2 testPos = (chunk->position + (chunk->GetCell(x, y).position)+ glm::vec2(0, -1)) * glm::vec2(4, 4);
					EditCell(testPos, {1,1}, ParticleSand);

					//std::cout << testPos.x << ", " << testPos.y << std::endl;

					continue;
				}

				if (chunk->GetCell(x, y - 1).Id == ParticleAir.Id)
				{
					chunk->SetCell(x, y, ParticleAir);
					chunk->SetCell(x, y - 1, ParticleSand);
				}
				else if (chunk->GetCell(x + 1, y - 1).Id == ParticleAir.Id)
				{
					chunk->SetCell(x, y, ParticleAir);
					chunk->SetCell(x + 1, y - 1, ParticleSand);
				}
				else if (chunk->GetCell(x - 1, y - 1).Id == ParticleAir.Id)
				{
					chunk->SetCell(x, y, ParticleAir);
					chunk->SetCell(x - 1, y - 1, ParticleSand);
				}
			}
		}
	}
}

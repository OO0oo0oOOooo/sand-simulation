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
		}
	}
}


void World::Update(float deltaTime)
{
	if(dirtyCells.size() <= 0)
		return;

	std::cout << dirtyCells.size() << std::endl;

	for(unsigned int i = 0; i < dirtyCells.size(); i++)
	{
		Cell cell = dirtyCells[i];
		glm::vec2 position = cell.position;
		bool hasMoves = false;

		glm::vec2 Neighbours[8] = 
		{
			position + glm::vec2( 0, -1), // Bot
			position + glm::vec2(-1, -1), // Bot Left
			position + glm::vec2( 1, -1), // Bot Right
			position + glm::vec2(-1,  0), // Left
			position + glm::vec2( 1,  0), // Right
			position + glm::vec2( 0,  1), // Top
			position + glm::vec2(-1,  1), // Top Left
			position + glm::vec2( 1,  1), // Top Right
		};

		Chunk* chunk = GetChunkFromWorldPos(position);
		Chunk* chunk0 = nullptr;

		if (cell.Id == ParticleSand.Id)
		{

			for (int j = 0; j <= 2; j++)
			{
				chunk0 = GetChunkFromWorldPos(Neighbours[j]);

				if (chunk0->GetCell(Neighbours[j], WorldSpace).Id == ParticleAir.Id)
				{
					chunk->SetCell(position, ParticleAir, WorldSpace);
					chunk0->SetCell(Neighbours[j], ParticleSand, WorldSpace);

					dirtyCells[i] = chunk0->GetCell(Neighbours[j], WorldSpace);
					dirtyCells.push_back(chunk->GetCell(position, WorldSpace));
					hasMoves = true;

					break;
				}

			}
		}

		if(!hasMoves)
			dirtyCells.erase(dirtyCells.begin() + i);

		// Do physics
		// position += velocity * deltaTime;
	}
}

//void World::UpdateChunks()
//{
//	for (int x = 0; x < numChunksWidth; x++)
//	{
//		for (int y = 0; y < numChunksHeight; y++)
//		{
//			Chunk* chunk = chunks[glm::vec2(x, y)];
//
//			/* && chunk->dirty*/
//			if (chunk != nullptr)
//			{
//				UpdateCells(chunk);
//			}
//		}
//	}
//}


//void World::UpdateCells(Chunk* chunk)
//{
//	// Update inside the chunk or Update outside the chunk then pass the data back in?
//
//
//	for (int x = 0; x < chunkSizeInCells; x++)
//	{
//		for (int y = 0; y < chunkSizeInCells; y++)
//		{
//			glm::vec2 cellPosition = chunk->position + glm::vec2(x, y);
//
//			if (cellPosition.y <= 0 || cellPosition.y >= 64 * 3 || cellPosition.x <= 0 || cellPosition.x >= 64 * 5)
//				continue;
//
//			if (chunk->GetCell(x, y).Id == ParticleSand.Id)
//			{
//				if (y % 64 == 0)
//				{
//					glm::vec2 testPos = (cellPosition + glm::vec2(0, -1)) * glm::vec2(4, 4);
//					Chunk* newChunk = chunks[GetChunkFromWorldPos(testPos, { 1, 1 })];
//
//					if (newChunk->GetCell(x, y + 63).Id == ParticleAir.Id)
//					{
//						chunk->SetCell(x, y, ParticleAir);
//						newChunk->SetCell(x, y+63, ParticleSand);
//					}
//
//					continue;
//				}
//
//				if (chunk->GetCell(x, y - 1).Id == ParticleAir.Id)
//				{
//					chunk->SetCell(x, y, ParticleAir);
//					chunk->SetCell(x, y - 1, ParticleSand);
//				}
//				else if (chunk->GetCell(x + 1, y - 1).Id == ParticleAir.Id)
//				{
//					chunk->SetCell(x, y, ParticleAir);
//					chunk->SetCell(x + 1, y - 1, ParticleSand);
//				}
//				else if (chunk->GetCell(x - 1, y - 1).Id == ParticleAir.Id)
//				{
//					chunk->SetCell(x, y, ParticleAir);
//					chunk->SetCell(x - 1, y - 1, ParticleSand);
//				}
//			}
//
//		}
//	}
//}

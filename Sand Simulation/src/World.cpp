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

	for(int i = 0; i < dirtyCells.size(); i++)
	{
		// dirtycells is just a copy not a refrence to the actual cell
		Cell cell = dirtyCells[i];
		glm::vec2 position = cell.position;

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

		if (cell.Id == ParticleSand.Id)
		{
			Chunk* chunk = GetChunkFromWorldPos(position);
			Chunk* chunk0 = GetChunkFromWorldPos(Neighbours[0]);

			if (chunk0->GetCell(Neighbours[0], WorldSpace).Id == ParticleAir.Id)
			{
				chunk0->SetCell(Neighbours[0], ParticleSand, WorldSpace);
				chunk->SetCell(position, ParticleAir, WorldSpace);

				dirtyCells.push_back(chunk0->GetCell(Neighbours[0], WorldSpace));
			}
		}

		// Set cell dirty flag to true when setting a cell
		// check if cell below is dirty during move interaction
		// if it is then dont remove this from the dirty list so it can be checked again
		dirtyCells.erase(dirtyCells.begin() + i);

		// Check neighbours for interaction
		//for (int j = 0; j < 8; j++)
		//{
		//	// Do interactions
		//}
		// if cell has no interactions available set dirty to false

		// Do physics
		// position += velocity * deltaTime;

		// if this is a react case then set the cell to reaction result
		// if this is a move case Swap with the cell we are interacting with
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

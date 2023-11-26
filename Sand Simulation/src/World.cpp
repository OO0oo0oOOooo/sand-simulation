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

void World::Update(float deltaTime)
{
	// Dirty Quad algorithm find and stores all the cells i need to update.
	// Then i can update all cells from the world position.
	// 
	// Dirty Cells array holds all the cells that need to be updated.
	// 
	for(int i = 0; i < dirtyCells.size(); i++)
	{
		// Get cells world position
		glm::vec2 position = dirtyCells[i].position;

		// Get Neighbours
		glm::vec2 NeighbourTable[8] = 
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

		// Check neighbours for interaction
		for (int j = 0; j < 8; j++)
		{
			// Do interactions
		}

		// Do physics
		// position += velocity * deltaTime;

		// if cell has not changed set dirty to false


		Chunk* chunk = chunks[GetChunkFromWorldPos(position, { 1, 1 })];
		chunk->SetCellFromWorldPos(position.x, position.y, dirtyCells[i]);
	}
	// 
	
	 
	// Check neighbours for interaction
	// Do interactions
	// Do physics
	// 
	// if cell has not changed set dirty to false
	// 
	// 
	// 
	// chunk = GetChunkFromWorldPos(x, y)
	// chunk->SetCellWorldPos(x, y)
	


	// Update cells
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
//			// Get Chunk position world
//			// Get cell position world
//			// check cell neighbours
//			
//			// Update chunks
//
//
//
//
//			/*if (chunk->GetCell(x, y).Id == ParticleSand.Id)
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
//			}*/
//
//		}
//	}
//}

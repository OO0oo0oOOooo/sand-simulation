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
	// Multi-threading
	// if any thread is idle, give it a chunk to fully check

	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			Chunk* chunk = chunks[glm::vec2(x, y)];

			if (chunk != nullptr)
			{
				chunk->UpdateActive();
			}
		}
	}
}

//void World::Update(float deltaTime)
//{
//	// Multi-threading
//	// if any thread is idle, give it a chunk to slow update
//
//	
//	// velocity = acceleration * deltaTime;
//
//
//	if (dirtyCells.size() <= 0)
//	{
//		UpdateChunks();
//		return;
//	}
//
//	std::cout << dirtyCells.size() << std::endl;
//
//	for(unsigned int i = 0; i < dirtyCells.size(); i++)
//	{
//		Cell cell = dirtyCells[i];
//		glm::vec2 position = cell.position;
//		bool hasMoves = false;
//
//		glm::vec2 Neighbours[8] = 
//		{
//			position + glm::vec2( 0, -1), // Bot
//			position + glm::vec2(-1, -1), // Bot Left
//			position + glm::vec2( 1, -1), // Bot Right
//			position + glm::vec2(-1,  0), // Left
//			position + glm::vec2( 1,  0), // Right
//			position + glm::vec2( 0,  1), // Top
//			position + glm::vec2(-1,  1), // Top Left
//			position + glm::vec2( 1,  1), // Top Right
//		};
//
//		Chunk* chunk = GetChunkFromWorldPos(position);
//		Chunk* chunk0 = nullptr;
//
//		if (cell.Id == ParticleSand.Id)
//		{
//
//			for (int j = 0; j <= 2; j++)
//			{
//				chunk0 = GetChunkFromWorldPos(Neighbours[j]);
//
//				if (chunk0->GetCell(Neighbours[j], WorldSpace).Id == ParticleAir.Id)
//				{
//					chunk->SetCell(position, ParticleAir, WorldSpace);
//					chunk0->SetCell(Neighbours[j], ParticleSand, WorldSpace);
//
//					dirtyCells[i] = chunk0->GetCell(Neighbours[j], WorldSpace);
//					dirtyCells.push_back(chunk->GetCell(position, WorldSpace));
//					hasMoves = true;
//
//					chunk->dirty = true;
//					chunk0->dirty = true;
//
//					break;
//				}
//			}
//		}
//
//		if(!hasMoves)
//			dirtyCells.erase(dirtyCells.begin() + i);
//
//		// Do physics
//		// position += velocity * deltaTime;
//	}
//}
//
//void World::UpdateChunks()
//{
//	for (int x = 0; x < numChunksWidth; x++)
//	{
//		for (int y = 0; y < numChunksHeight; y++)
//		{
//			Chunk* chunk = chunks[glm::vec2(x, y)];
//
//			if (chunk != nullptr && chunk->dirty)
//			{
//				UpdateCells(chunk);
//			}
//		}
//	}
//}
//
//void World::UpdateCells(Chunk* chunk)
//{
//	std::cout << chunk->position.x << ", " << chunk->position.y << std::endl;
//	for (int x = 0; x < chunkSizeInCells; x++)
//	{
//		for (int y = 0; y < chunkSizeInCells; y++)
//		{
//			Cell cell = chunk->GetCell(glm::vec2(x, y), LocalSpace);
//			glm::vec2 position = cell.position;
//
//			glm::vec2 Neighbours[8] =
//			{
//				position + glm::vec2(0, -1), // Bot
//				position + glm::vec2(-1, -1), // Bot Left
//				position + glm::vec2(1, -1), // Bot Right
//				position + glm::vec2(-1,  0), // Left
//				position + glm::vec2(1,  0), // Right
//				position + glm::vec2(0,  1), // Top
//				position + glm::vec2(-1,  1), // Top Left
//				position + glm::vec2(1,  1), // Top Right
//			};
//
//			if (cell.Id == ParticleSand.Id)
//			{
//				for (int j = 0; j <= 0; j++)
//				{
//					Chunk* newChunk = GetChunkFromWorldPos(Neighbours[j]);
//
//					if (newChunk->GetCell(Neighbours[j], WorldSpace).Id == ParticleAir.Id)
//					{
//						//chunk->SetCell(position, ParticleAir, WorldSpace);
//						//newChunk->SetCell(Neighbours[j], ParticleSand, WorldSpace);
//						dirtyCells.push_back(chunk->GetCell(position, WorldSpace));
//					}
//
//				}
//			}
//		}
//	}
//
//	chunk->dirty = false;
//
//}

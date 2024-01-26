#include "World.h"

World::World(ctpl::thread_pool* pool)
	: threadPool(pool)
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			chunks[glm::vec2(x, y)] = new Chunk(this, x * 64, y * 64);
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

//void World::Render(Shader* shader)
//{
//	for (int x = 0; x < numChunksWidth; x++)
//	{
//		for (int y = 0; y < numChunksHeight; y++)
//		{
//			Chunk* chunk = chunks[glm::vec2(x, y)];
//
//			if(chunk != nullptr)
//			{
//				//chunk->UpdateMesh();
//				chunk->DrawMesh(shader);
//			}
//		}
//	}
//
//	
//}

void CellularAutomata(int id, Chunk* chunk)
{
	//std::cout << "Thread: " << id << " || Chunk XY: " << chunk->position.x << ", " << chunk->position.y << std::endl;
	chunk->UpdateActive();
}

void World::Update(Shader* shader)
{
	for (int pass = 0; pass < 4; ++pass)
	{
		std::vector<std::pair<std::future<void>, Chunk*>> futures;

		for (int y = 0; y < numChunksHeight; y++)
		{
			for (int x = 0; x < numChunksWidth; x++)
			{

				if ((x + y + pass) % 4 == 0)
				{
					Chunk* chunk = chunks[glm::vec2(x, y)];

					if (chunk != nullptr /*&& chunk->dirty*/)
					{
						futures.push_back(std::make_pair(threadPool->push(CellularAutomata, chunk), chunk));
					}
				}

			}
		}

		for (auto& f : futures)
		{
			f.first.get();
			f.second->UploadMeshData();
			f.second->DrawMesh(shader);
		}
	}
}

void World::DrawChunkBorders(Shader* shader)
{
	for (int x = 0; x < numChunksWidth; x++)
	{
		for (int y = 0; y < numChunksHeight; y++)
		{
			int cx = (x * 64) * cellSize;
			int cy = (y * 64) * cellSize;

			std::vector<Vertex> vertices = {
				{{cx, cy, 0.1f}, {0.1, 1.0, 0.1, 1}},
				{{cx + (64 * cellSize), cy, 0.1f}, {0.1, 1.0, 0.1, 1}},
				{{cx + (64 * cellSize), cy + (64 * cellSize), 0.1f}, {0.1, 1.0, 0.1, 1}},
				{{cx, cy + (64 * cellSize), 0.1f}, {0.1, 1.0, 0.1, 1}},
			};

			std::vector<unsigned int> indices = {
				0, 1, // Bottom edge
				1, 2, // Right edge
				2, 3, // Top edge
				3, 0  // Left edge
			};

			Mesh squareOutline;
			squareOutline.vertices = vertices;
			squareOutline.indices = indices;
			squareOutline.UploadVBOData();
			squareOutline.UploadIBOData();

			squareOutline.DrawLine(shader);

			chunks[glm::vec2(x, y)]->DrawDirtyQuad(shader);
		}
	}
}
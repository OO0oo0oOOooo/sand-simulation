#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, int x, int y)
	: position(x, y), dirty(false), world(world)
{
	ChunkData = std::vector<Cell>(chunkSizeInCells * chunkSizeInCells);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			ChunkData[GetCellIndex(x, y)] = ParticleAir;
		}
	}

	mesh = new Mesh();
	CreateMesh();
}

Chunk::~Chunk()
{
	delete mesh;
}

void Chunk::CreateMesh()
{
	mesh->vertices.resize(chunkSizeInCells * chunkSizeInCells * 4);
	mesh->indices.resize(chunkSizeInCells * chunkSizeInCells * 6);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			int cellIndex = GetCellIndex(x, y);

			int baseVertexIndex = (cellIndex) * 4;
			int baseIndexIndex = (cellIndex) * 6;
			Cell& cell = ChunkData[cellIndex];

			int newX = x + (int)position.x;
			int newY = y + (int)position.y;

			for (int i = 0; i < 4; i++)
			{
				mesh->vertices[baseVertexIndex + i].position = (glm::vec3(newX, newY, 0) + vertexPositions[i]) * (float)cellSize;
				mesh->vertices[baseVertexIndex + i].color = cell.color;
			}

			for (int i = 0; i < 6; i++)
			{
				mesh->indices[baseIndexIndex + i] = meshTriangles[i] + baseVertexIndex;
			}
		}
	}

	mesh->UploadIBOData();
	mesh->UploadVBOData();
}

void Chunk::DrawMesh(Shader* shader)
{
	mesh->Draw(shader);
}

void Chunk::RecalculateBounds()
{
	bounds.min = ActiveCells[0];
	bounds.max = ActiveCells[0];

	for (unsigned int i = 0; i < ActiveCells.size(); i++)
	{
		bounds.min.x = std::min(bounds.min.x, ActiveCells[i].x);
		bounds.min.y = std::min(bounds.min.y, ActiveCells[i].y);
		bounds.max.x = std::max(bounds.max.x, ActiveCells[i].x);
		bounds.max.y = std::max(bounds.max.y, ActiveCells[i].y);
	}

	bounds.size = (bounds.max - bounds.min) + 1;
	bounds.position = bounds.min;
}

// Particle ID | Neighbor Index | Neighbor ID

// Cell Ids
// 1 = Air
// 2 = Sand
// 3 = Water

// Neighbor Index
// 0 = Bot
// 1 = Bot Left
// 2 = Bot Right
// 3 = Left
// 4 = Right
// 5 = Top
// 6 = Top Left
// 7 = Top Right

std::map<int, int> LUT = {
	//Sand
	{201, 1 },
	{202, 0 },
	{203, 1 },

	{211, 1 },
	{212, 0 },
	{213, 1 },

	{221, 1 },
	{222, 0 },
	{223, 1 },


	// Water
	{301, 1 },
	{302, 0 },
	{303, 0 },

	{311, 1 },
	{312, 0 },
	{313, 0 },

	{321, 1 },
	{322, 0 },
	{323, 0 },

	{331, 1 },
	{332, 0 },
	{333, 0 },

	{341, 1 },
	{342, 0 },
	{343, 0 },
};

void SwapCells(Chunk* chunk, glm::ivec2 cellPosition, Cell Neighbour, glm::ivec2 neighbourPosition)
{
	chunk->SetCell(cellPosition, ParticleAir, WorldSpace);
	chunk->world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, ParticleSand, WorldSpace);
}

void Chunk::UpdateActive()
{
	if (ActiveCells.size() <= 0)
		return;

	RecalculateBounds();

	if (bounds.size.x <= 0 || bounds.size.y <= 0)
		return;

	for (int y = 0; y < bounds.size.y; y++)
	{
		bool alternate = (y % 2 == 0);
		int startX = alternate ? 0 : bounds.size.x - 1;
		int endX = alternate ? bounds.size.x : -1;
		int stepX = alternate ? 1 : -1;

		for (int x = startX; x != endX; x += stepX)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);
			Cell cell = GetCell(boundsPosition, LocalSpace);
			glm::ivec2 cellPosition = cell.position;

			//ParticleUpdate(this, cell, cellPosition);
			// SwapCells(this, cellPosition, neighbour, neighbourPosition);

			bool shouldBreak = false;

			for (int j = 0; j < 8; j++)
			{
				glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
				Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

				int key = cell.Id * 100 + j * 10 + neighbour.Id;

				auto it = LUT.find(key);

				if (it != LUT.end()) 
				{ 
					switch (LUT[key])
					{
						case 0:
							std::cout << "No Result" << std::endl;
							break;

						case 1:
						{
							SetCell(cellPosition, neighbour, WorldSpace);
							world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, cell, WorldSpace);
							shouldBreak = true;
							break;
						}

						case 2:
						{
							std::cout << "Cell Reaction" << std::endl;
							shouldBreak = true;
							return;
						}

						default:
							break;
					}
				}

				if(shouldBreak)
					break;

				/*if (neighbour.Id == ParticleAir.Id)
				{
					Cell particle = ParticleSand;

					chunk->SetCell(cellPosition, ParticleAir, WorldSpace);
					chunk->world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, particle, WorldSpace);

					break;
				}*/
			}

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}
}



/*if (cell.Id == ParticleSand.Id)
			{
				for (int j = 0; j <= 2; j++)
				{
					glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
					Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

					if (neighbour.Id == ParticleAir.Id)
					{
						Cell particle = ParticleSand;

						SetCell(cell.position, ParticleAir, WorldSpace);
						world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, particle, WorldSpace);

						break;
					}
				}
			}

			else if (cell.Id == ParticleWater.Id)
			{
				for (int j = 0; j <= 4; j++)
				{

					glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
					Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

					if (neighbour.Id == ParticleAir.Id)
					{
						Cell particle = ParticleWater;

						SetCell(cell.position, ParticleAir, WorldSpace);
						world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, particle, WorldSpace);

						break;
					}
				}
			}*/
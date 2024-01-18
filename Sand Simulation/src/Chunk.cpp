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
			ChunkData[GetCellIndex(x, y)] = AIR;
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

// Particle ID | Neighbor Index | Neighbor ID

std::map<int, int> LUT = {

	//Sand-Air
	{300, 1 },
	{301, 1 },
	{302, 1 },

	//Sand-Water
	{340, 1 },
	{341, 1 },
	{342, 1 },

	// Water-Air
	{400, 1 },
	{401, 1 },
	{402, 1 },
	{403, 1 },
	{404, 1 },
};

//#include <string>

std::map<std::string, std::string> FULL_LUT = {
	// bot, Middle, top
	// Sand
	{"000030000", "030000000"},
	{"****3****", "030000000"},

	{"121 121 111", 1},
	{"221 121 111", 1},

	// Water
	{"*** *3* *_*", "*** *_* *3*"},
	{"*** *3* _3_", "*** *3* _3_"},

};

// Water Move Map
// {0, 0, 0}
// {1, *, 1}
// {2, 3, 2}
// 
// Water should find the lowest point and flow down.
// Iterate through the neighbours and move toward the highest score available.
// 
// Can Move through
// AIR

// Water Interaction Map
// {WATER + FIRE, STEAM}
// {WATER + LAVA, ROCK}


void Chunk::UpdateActive()
{
	if (ActiveCells.size() <= 0)
		return;

	RecalculateBounds();

	if (bounds.size.x <= 0 || bounds.size.y <= 0)
		return;

	for (int y = 0; y < bounds.size.y; y++)
	{
		for (int x = 0; x < bounds.size.x; x++)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);
			Cell cell = GetCell(boundsPosition, LocalSpace);
			glm::ivec2 cellPosition = cell.position;
			bool shouldBreak = false;

			unsigned char key[] = {
				{0},{0},{0},

				{0},{0},{0},

				{0},{0},{0},
			};

			for (int j = 0; j < 9; j++)
			{
				glm::ivec2 neighbourPosition = cellPosition + NeighbourTable2[j];
				Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

				key[j] = neighbour.Id;
			}



			std::cout << "\n" << (int)key[0] << (int)key[1] << (int)key[2] << "\n" << (int)key[3] << (int)key[4] << (int)key[5] << "\n" << (int)key[6] << (int)key[7] << (int)key[8] << std::endl;

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}

	/*for (int y = 0; y < bounds.size.y; y++)
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
			bool shouldBreak = false;

			for (int j = 0; j < 8; j++)
			{
				glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
				Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

				int key = cell.Id * 100 + neighbour.Id * 10 + j;

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
			}

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}*/
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
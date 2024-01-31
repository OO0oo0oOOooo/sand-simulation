#include "Chunk.h"
#include "World.h"

#include "CellInteractions.h"

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

//void Chunk::ComputeNextChunk()
//{
//	std::vector<Cell> newChunkData = ChunkData;
//
//	for (int y = 0; y < chunkSizeInCells; y++)
//	{
//		for (int x = 0; x < chunkSizeInCells; x++)
//		{
//			int index = GetCellIndex(x, y);
//			int belowIndex = GetCellIndex(x, y - 1);
//
//			if(index == -1 || belowIndex == -1)
//				continue;
//
//			Cell cell = ChunkData[index];
//			Cell belowCell = ChunkData[belowIndex];
//
//			if(cell.Id == AIR.Id)
//				continue;
//
//			if (cell.Id == SAND.Id)
//			{
//				if (belowCell.Id == AIR.Id)
//				{
//					newChunkData[index] = belowCell;
//					newChunkData[belowIndex] = cell;
//
//					int baseVertexIndex = index * 4;
//					int baseVertexIndex2 = belowIndex * 4;
//
//					for (int i = 0; i < 4; i++)
//					{
//						Vertex v;
//
//						v.position = (glm::vec3(x + position.x, y + position.y , 0) + vertexPositions[i]) * (float)cellSize;
//						v.color = cell.color;
//
//						mesh->vertices[baseVertexIndex + i] = v;
//					}
//
//					for (int i = 0; i < 4; i++)
//					{
//						Vertex v;
//
//						v.position = (glm::vec3(x + position.x, (y - 1) + position.y, 0) + vertexPositions[i]) * (float)cellSize;
//						v.color = cell.color;
//
//						mesh->vertices[baseVertexIndex2 + i] = v;
//					}
//				}
//			}
//		}
//	}
//
//	ChunkData = newChunkData;
//}

// Requirements
// Update cells within the bounds
// Update across borders
// Dont Update the same cell twice or Double buffer

void Chunk::ComputeNextChunk()
{
	std::vector<Cell> newChunkData = ChunkData;

	for (int y = 0; y < chunkSizeInCells; y++)
	{
		for (int x = 0; x < chunkSizeInCells; x++)
		{
			int index = GetCellIndex(x, y);
			int belowIndex = GetCellIndex(x, y - 1);

			if (index == -1 || belowIndex == -1)
				continue;

			Cell cell = ChunkData[index];
			Cell belowCell = ChunkData[belowIndex];

			if (cell.Id == AIR.Id)
				continue;

			if (cell.Id == SAND.Id)
			{
				if (belowCell.Id == AIR.Id)
				{
					newChunkData[index] = belowCell;
					newChunkData[belowIndex] = cell;

					int baseVertexIndex = index * 4;
					int baseVertexIndex2 = belowIndex * 4;

					for (int i = 0; i < 4; i++)
					{
						Vertex v;

						v.position = (glm::vec3(x + position.x, y + position.y, 0) + vertexPositions[i]) * (float)cellSize;
						v.color = cell.color;

						mesh->vertices[baseVertexIndex + i] = v;
					}

					for (int i = 0; i < 4; i++)
					{
						Vertex v;

						v.position = (glm::vec3(x + position.x, (y - 1) + position.y, 0) + vertexPositions[i]) * (float)cellSize;
						v.color = cell.color;

						mesh->vertices[baseVertexIndex2 + i] = v;
					}
				}
			}
		}
	}

	ChunkData = newChunkData;
}


// Improvements
// 1. Create a list of cells that have moved
// 
// 2. Cross Chunk Update only when needed
// 
// 3. Move cells using velocity
//

struct KeyHash {
	std::size_t operator()(const glm::ivec2& k) const {
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}
};

//std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;

void Chunk::UpdateActive()
{

	if (ActiveCells.size() <= 0)
		return;

	RecalculateBounds();

	if (bounds.size.x <= 0 || bounds.size.y <= 0)
		return;

	// Create something to keep track of the cells that have moved
	std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;
	

	for (int y = 0; y < bounds.size.y; y++)
	{
		for (int x = 0; x < bounds.size.x; x++)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);

			Cell cell = GetCell(boundsPosition, LocalSpace);
			int index = GetCellIndex(boundsPosition);
			glm::ivec2 cellPosition = cell.position;

			bool shouldBreak = false;

			// If the cell has already moved then dont move it again
			//auto it1 = hasMoved.find(cellPosition);

			//if(it1->second)
			//	continue;

			if (hasMoved[cellPosition])
				continue;  

			for (int j = 0; j < 8; j++)
			{
				glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
				Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

				int id = (int)cell.Id;
				int neighbourId = (int)neighbour.Id;

				auto it = LUT[id][neighbourId].find(j);
				
				if (it != LUT[id][neighbourId].end())
				{
					int* res = it->second;

					SetCell(cellPosition, CellTable[res[0]], WorldSpace);
					world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, CellTable[res[1]], WorldSpace);

					hasMoved[neighbourPosition] = true;

					shouldBreak = true;
					break;
				}

				if (shouldBreak)
					break;

			}

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}

	//hasMoved.clear();
}



//std::map<int, int> LUT = {
//
//	//Sand-Air
//	{300, 1 },
//	{301, 1 },
//	{302, 1 },
//
//	//Sand-Water
//	{340, 1 },
//	{341, 1 },
//	{342, 1 },
//
//	// Water-Air
//	{400, 1 },
//	{401, 1 },
//	{402, 1 },
//	{403, 1 },
//	{404, 1 },
//
//	// Water-Lava
//	{451, 2},
//	{453, 2},
//	{455, 2},
//	{457, 2},
//
//
//};

//std::map<std::string, std::string> LUT2 = {
//
//	//Sand-Air
//	{"300", "030"},
//	{"301", "031"},
//	{"302", "032"},
//
//	//Sand-Water
//	{"340", "430"},
//	{"341", "431"},
//	{"342", "432"},
//
//	// Water-Air
//	{"400", "040"},
//	{"401", "041"},
//	{"402", "042"},
//	{"403", "043"},
//	{"404", "044"},
//
//	// Water-Lava
//	{"451", "011"},
//	{"453", "013"},
//	{"455", "015"},
//	{"457", "017"},
//
//	//Lava-Air
//	{"500", "050"},
//	{"501", "051"},
//	{"502", "052"},
//	{"503", "053"},
//	{"504", "054"},
//};

//std::map<std::string, std::string> Water_LUT = {
//
//	{"000 040 000", "000 000 000"}, // Default State
//
//	// Water-Lava = Stone
//	{"000 040 050", "000 000 010"},
//	{"000 045 000", "000 001 000"},
//	{"000 540 000", "000 100 000"},
//	{"050 040 000", "010 000 000"},
//
//	// The issue with this is that if i have anyting but an air cell in the key it will not work.
//
//	// I need to find a way that will just look at the interacting cells and not the whole map. modify it then return it
//};

/*std::string key;
key = std::to_string(cell.Id) + std::to_string(neighbour.Id) + std::to_string(j);

auto it = LUT2.find(key);
if (it != LUT2.end())
{
	std::string s = it->second;

	int id = s[0] - '0';
	int neighbourId = s[1] - '0';
	int index = s[2] - '0';

	SetCell(cellPosition, CellTable[id], WorldSpace);
	world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, CellTable[neighbourId], WorldSpace);

	shouldBreak = true;
	break;
}*/

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
//
// Water Interaction Map
// {WATER + FIRE, STEAM}
// {WATER + LAVA, ROCK}

/*if (it != LUT.end())
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
}*/

/*unsigned char key[] = {
	{0},{0},{0},

	{0},{0},{0},

	{0},{0},{0},
};

for (int j = 0; j < 9; j++)
{
	glm::ivec2 neighbourPosition = cellPosition + NeighbourTable2[j];
	Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

	key[j] = neighbour.Id;
}*/

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
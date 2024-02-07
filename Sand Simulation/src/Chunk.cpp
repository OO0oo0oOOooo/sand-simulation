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

//void Chunk::UpdateActive()
//{
//	if (ActiveCells.size() <= 0)
//		return;
//
//	RecalculateBounds();
//
//	if (bounds.size.x <= 0 || bounds.size.y <= 0)
//		return;
//
//	std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;
//
//	for (int y = 0; y < bounds.size.y; y++)
//	{
//		for (int x = 0; x < bounds.size.x; x++)
//		{
//			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);
//
//			Cell cell = GetCell(boundsPosition, LocalSpace);
//			int index = GetCellIndex(boundsPosition);
//			glm::ivec2 cellPosition = cell.position;
//
//			bool shouldBreak = false;
//
//			if (hasMoved[cellPosition])
//				continue;
//
//			for (int j = 0; j < 8; j++)
//			{
//				glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
//				Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);
//
//				int id = (int)cell.Id;
//				int neighbourId = (int)neighbour.Id;
//
//				auto it = LUT[id][neighbourId].find(j);
//				
//				if (it != LUT[id][neighbourId].end())
//				{
//					int* res = it->second;
//
//					SetCell(cellPosition, CellTable[res[0]], WorldSpace);
//					world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, CellTable[res[1]], WorldSpace);
//
//					hasMoved[neighbourPosition] = true;
//
//					shouldBreak = true;
//					break;
//				}
//
//				if (shouldBreak)
//					break;
//
//			}
//
//			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
//		}
//	}
//}

void Chunk::UpdateActive(float deltaTime)
{
	if (ActiveCells.size() <= 0)
		return;

	RecalculateBounds();

	if (bounds.size.x <= 0 || bounds.size.y <= 0)
		return;

	std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;

	for (int y = 0; y < bounds.size.y; y++)
	{
		for (int x = 0; x < bounds.size.x; x++)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);

			Cell cell = GetCell(boundsPosition, LocalSpace);
			int index = GetCellIndex(boundsPosition);
			glm::ivec2 cellPosition = cell.position;
			int id = (int)cell.Id;

			bool shouldBreak = false;

			if (hasMoved[cellPosition])
				continue;

			switch (id)
			{
				case 3:
					SandUpdate(cell, deltaTime);
					break;

				case 4:
					//WaterUpdate(cell);
					break;

				default:
					break;
			}

			/*
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
			*/

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}
}

/*void Chunk::UpdateActive()
{

	std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;

	for (int y = 0; y < chunkSizeInCells; y++)
	{
		for (int x = 0; x < chunkSizeInCells; x++)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);

			Cell cell = GetCell(boundsPosition, LocalSpace);
			int index = GetCellIndex(boundsPosition);
			glm::ivec2 cellPosition = cell.position;
			int id = (int)cell.Id;

			bool shouldBreak = false;

			if (hasMoved[cellPosition])
				continue;

			switch (id)
			{
				case 3:
					SandUpdate(cell);
					break;

				default:
					break;
			}
		}
	}
}
*/

void Chunk::SandUpdate(Cell cell, float deltaTime)
{	
	glm::vec2 vel = cell.velocity;
	//vel.y += -9.81f * deltaTime;
	vel.y += -1 * deltaTime;

	glm::ivec2 newPos = cell.position + vel;

	Cell neighbour = world->GetChunkFromWorldPos(newPos)->GetCell(newPos, WorldSpace);

	if (neighbour.Id == AIR.Id)
	{
		cell.velocity = vel;
		SetCell(cell.position, AIR, WorldSpace);
		world->GetChunkFromWorldPos(newPos)->SetCell(newPos, cell, WorldSpace);

		return;
	}
	else
	{
		vel.y = 0;
	}

	cell.velocity = vel;
}

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
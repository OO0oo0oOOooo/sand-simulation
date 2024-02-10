#include "Chunk.h"
#include "World.h"

#include "CellInteractions.h"

Chunk::Chunk(World* world, int x, int y)
	: position(x, y), world(world)
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

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}
}

//void Chunk::SandUpdate(Cell cell, float deltaTime)
//{	
//	glm::vec2 vel = cell.velocity;
//	//vel.y += -9.81f * deltaTime;
//	vel.y += -3 * deltaTime;
//
//	glm::ivec2 newPos = cell.position + vel;
//
//	Chunk* neighbourChunk = world->GetChunkFromWorldPos(newPos);
//
//	Cell neighbour = neighbourChunk->GetCell(newPos, WorldSpace);
//	
//	world->ChunksToUpdate.insert(this);
//	world->ChunksToUpdate.insert(neighbourChunk);
//
//	if (neighbour.Id == AIR.Id)
//	{
//		cell.velocity = vel;
//		SetCell(cell.position, AIR, WorldSpace);
//
//		Chunk* chunk = world->GetChunkFromWorldPos(newPos);
//		chunk->SetCell(newPos, cell, WorldSpace);
//
//		return;
//	}
//	else
//	{
//		vel.y = 0;
//	}
//
//	cell.velocity = vel;
//}

void Chunk::SandUpdate(Cell cell, float deltaTime)
{
	// Recursively move the sand down one until it hits ground or the destination for this frame

	bool canBreak = false;

	glm::vec2 vel = cell.velocity;
	//vel.y += -9.81f * deltaTime;
	vel.y += -3 * deltaTime;
	
	glm::ivec2 currentPosition = cell.position;
	glm::ivec2 targetPosition = cell.position + vel;
	
	
	int i = 0;
	while (currentPosition != targetPosition)
	{
		glm::ivec2 nextPosition = currentPosition + glm::ivec2(0, -i);

		Chunk* neighbourChunk = world->GetChunkFromWorldPos(nextPosition);
		Cell nextCell = neighbourChunk->GetCell(nextPosition, WorldSpace);

		if (nextCell.Id == AIR.Id)
		{
			cell.velocity = vel;
		}

		// Not air then preform cellular automata and break loop


		i++;
	}

	
	/*Chunk* neighbourChunk = world->GetChunkFromWorldPos(targetPosition);
	Cell belowNeighbour = neighbourChunk->GetCell(targetPosition, WorldSpace);

	if (belowNeighbour.Id == AIR.Id)
	{
		cell.velocity = vel;
		SetCell(cell.position, AIR, WorldSpace);

		Chunk* chunk = world->GetChunkFromWorldPos(targetPosition);
		chunk->SetCell(targetPosition, cell, WorldSpace);

		world->ChunksToUpdate.insert(this);
		world->ChunksToUpdate.insert(neighbourChunk);

	}
	else
	{
		vel.y = 0;
	}*/
	
	//
	//cell.velocity = vel;

	//if (canBreak)
	//	return;
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
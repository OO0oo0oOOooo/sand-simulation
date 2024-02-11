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
//	cell.velocity.y += -9.81f * deltaTime;
//	glm::vec2 newPos = cell.position + cell.velocity;
//	
//	Chunk* chunk = world->GetChunkFromWorldPos(newPos);
//
//	SetCell(cell.position, AIR, WorldSpace);
//	chunk->SetCell(newPos, cell, WorldSpace);
//
//	world->ChunksToUpdate.insert(this);
//	world->ChunksToUpdate.insert(chunk);
//
//	/*if (neighbour.Id == AIR.Id)
//	{
//		
//
//		return;
//	}
//	else
//	{
//		vel.y = 0;
//	}
//
//	cell.velocity = vel;*/
//
//}

void Chunk::SandUpdate(Cell cell, float deltaTime)
{
	glm::vec2 vel = cell.velocity;
	vel.y += -9.81f * deltaTime;

	glm::vec2 currentPosition = cell.position;
	glm::vec2 targetPosition = currentPosition + vel;

	int x1 = currentPosition.x;
	int y1 = currentPosition.y;

	int x2 = targetPosition.x;
	int y2 = targetPosition.y;

	int xDiff = x2 - x1;
	int yDiff = y2 - y1;

	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

	int xModifier = xDiff > 0 ? 1 : -1;
	int yModifier = yDiff > 0 ? 1 : -1;

	int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
	int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));

	float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));

	int shorterSideIncrease;

	for (int i = 1; i <= longerSideLength; i++) {
		shorterSideIncrease = glm::round(i * slope);
		int yIncrease, xIncrease;
		if (xDiffIsLarger) {
			xIncrease = i;
			yIncrease = shorterSideIncrease;
		}
		else {
			yIncrease = i;
			xIncrease = shorterSideIncrease;
		}
		int currentY = y1 + (yIncrease * yModifier);
		int currentX = x1 + (xIncrease * xModifier);

		glm::vec2 step = { currentX, currentY };
		Chunk* stepChunk = world->GetChunkFromWorldPos(step);
		Cell stepCell = stepChunk->GetCell(step, WorldSpace);

		if (stepCell.Id == AIR.Id)
		{
			SetCell({ x1, y1 }, AIR, WorldSpace);
			stepChunk->SetCell(step, cell, WorldSpace);
		}
		else
		{
			cell.velocity = { 0, 0 };

		}
	}

	cell.velocity = vel;
}

//void Chunk::SandUpdate(Cell cell, float deltaTime)
//{
//	glm::vec2 vel = cell.velocity;
//	vel.y += -9.81f * deltaTime;
//
//	glm::vec2 currentPosition = cell.position;
//	glm::vec2 targetPosition = cell.position + vel;
//
//	//	int i = 0;
//	//	while (currentPosition != targetPosition)
//	//	{
//	//		glm::vec2 distance = targetPosition - currentPosition;
//	//		//std::cout << distance.x << " " << distance.y << std::endl;
//	//
//	//		if(distance.y )
//	//
//	//		/*
//	//		glm::ivec2 newPosition = ;
//	//
//	//		Chunk* neighbourChunk = world->GetChunkFromWorldPos(newPosition);
//	//		Cell nextCell = neighbourChunk->GetCell(newPosition, WorldSpace);
//	//
//	//		if (nextCell.Id == AIR.Id)
//	//		{
//	//			cell.velocity = vel;
//	//		}
//	//		*/
//	//
//	//		break;
//	//		i++;
//	//	}
//	//}
//
//	//Chunk* neighbourChunk = world->GetChunkFromWorldPos(targetPosition);
//	//Cell belowNeighbour = neighbourChunk->GetCell(targetPosition, WorldSpace);
//
//	//if (belowNeighbour.Id == AIR.Id)
//	//{
//	//	cell.velocity = vel;
//	//	SetCell(currentPosition, AIR, WorldSpace);
//
//	//	Chunk* chunk = world->GetChunkFromWorldPos(targetPosition);
//	//	chunk->SetCell(targetPosition, cell, WorldSpace);
//
//	//	world->ChunksToUpdate.insert(this);
//	//	world->ChunksToUpdate.insert(neighbourChunk);
//
//	//}
//	//else
//	//{
//	//	vel.y = 0;
//	//}
//	//
//	//cell.velocity = vel;
//}

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
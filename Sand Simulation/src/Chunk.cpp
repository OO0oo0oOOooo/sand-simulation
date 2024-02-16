#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, int cx, int cy) : Position(cx, cy), _world(world)
{
	_chunkData = std::vector<Element>(chunkSizeInCells * chunkSizeInCells);
	_mesh = new Mesh();

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			Air air;
			_chunkData[GetIndex({ x, y })] = air;
		}
	}

	CreateMesh();
}

Chunk::~Chunk()
{
	delete _mesh;
}

void Chunk::CreateMesh()
{
	_mesh->Clear();

	_mesh->vertices.resize(chunkSizeInCells * chunkSizeInCells * 4);
	_mesh->indices.resize(chunkSizeInCells * chunkSizeInCells * 6);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			int cellIndex = GetIndex({ x, y });

			int baseVertexIndex = (cellIndex) * 4;
			int baseIndexIndex = (cellIndex) * 6;
			Element element = _chunkData[cellIndex];

			int newX = x + (int)Position.x;
			int newY = y + (int)Position.y;

			for (int i = 0; i < 4; i++)
			{
				_mesh->vertices[baseVertexIndex + i].position = (glm::vec3(newX, newY, 0) + vertexPositions[i]) * (float)cellSize;
				_mesh->vertices[baseVertexIndex + i].color = element.Color;
			}

			for (int i = 0; i < 6; i++)
			{
				_mesh->indices[baseIndexIndex + i] = meshTriangles[i] + baseVertexIndex;
			}
		}
	}

	UploadMeshData();
}

void Chunk::Update()
{
	std::unordered_map<glm::vec2, bool, KeyHash> hasMoved;

	for (int y = 0; y < chunkSizeInCells; y++)
	{
		for (int x = 0; x < chunkSizeInCells; x++)
		{
			glm::ivec2 position = glm::ivec2(x, y);

			Element element = GetElementAtLocalPosition(position);
			int id = (int)element.ID;

			glm::ivec2 elementPosition = element.Position;
			if (hasMoved[elementPosition])
				continue;

			switch (id)
			{
			case 3:
				SandUpdate(element);
				break;

			case 4:
				//WaterUpdate(element);
				break;

			default:
				break;
			}
		}
	}
}

void Chunk::SandUpdate(Element element)
{
	glm::vec2 vel = element.Velocity;
	vel.y += -9.81f * Time::deltaTime;

	glm::vec2 currentPosition = element.Position;
	glm::vec2 targetPosition = currentPosition + vel;

	glm::vec2 lastStep = currentPosition;
	Chunk* lastStepChunk = this;

	int x1 = currentPosition.x;
	int y1 = currentPosition.y;

	int x2 = targetPosition.x;
	int y2 = targetPosition.y;

	int xDiff = x2 - x1;
	int yDiff = y2 - y1;

	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

	int xMod = xDiff > 0 ? 1 : -1;
	int yMod = yDiff > 0 ? 1 : -1;

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
		int currentY = y1 + (yIncrease * yMod);
		int currentX = x1 + (xIncrease * xMod);

		glm::vec2 step = { currentX, currentY };
		glm::ivec2 stepInt = { currentX, currentY };

		Chunk* stepChunk = _world->GetChunkFromWorldPos(step);
		Element stepCell = stepChunk->GetElementAtLocalPosition( stepInt - stepChunk->Position);

		if (stepCell.ID == 0)
		{
			element.Velocity = vel;

			lastStepChunk->SetElementAtWorldPosition(lastStep, stepCell);
			stepChunk->SetElementAtWorldPosition(step, element);

			lastStep = step;
			lastStepChunk = stepChunk;
		}
		else
		{
			element.Velocity = { 0, 0 };
			break;
		}
	}
}


/*
* Old Chunk

Chunk::Chunk(World* world, int x, int y)
	: position(x, y), world(world)
{
	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			ChunkData[x, y] = AIR;
			//SetChunkData({x,y}, element);
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
				ChunkMesh->vertices[baseVertexIndex + i].position = (glm::vec3(newX, newY, 0) + vertexPositions[i]) * (float)cellSize;
				ChunkMesh->vertices[baseVertexIndex + i].color = cell.color;
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

void Chunk::UpdateActive()
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
				SandUpdate(cell);
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

void Chunk::SandUpdate(Cell cell)
{
	glm::vec2 vel = cell.velocity;
	vel.y += -9.81f * Time::deltaTime;

	glm::vec2 currentPosition = cell.position;
	glm::vec2 targetPosition = currentPosition + vel;

	glm::vec2 lastStep = currentPosition;
	Chunk* lastStepChunk = this;

	int x1 = currentPosition.x;
	int y1 = currentPosition.y;

	int x2 = targetPosition.x;
	int y2 = targetPosition.y;

	int xDiff = x2 - x1;
	int yDiff = y2 - y1;

	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

	int xMod = xDiff > 0 ? 1 : -1;
	int yMod = yDiff > 0 ? 1 : -1;

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
		int currentY = y1 + (yIncrease * yMod);
		int currentX = x1 + (xIncrease * xMod);

		glm::vec2 step = { currentX, currentY };
		Chunk* stepChunk = world->GetChunkFromWorldPos(step);
		Cell stepCell = stepChunk->GetCell(step, WorldSpace);

		// This fixes the boarder drawing issue but is slow
		//world->ChunksToUpdate.insert(lastStepChunk);
		//world->ChunksToUpdate.insert(stepChunk);

		if (stepCell.Id == AIR.Id)
		{
			cell.velocity = vel;
			lastStepChunk->SetCell(lastStep, AIR, WorldSpace);
			stepChunk->SetCell(step, cell, WorldSpace);

			lastStep = step;
			lastStepChunk = stepChunk;
		}
		else
		{
			cell.velocity = { 0, 0 };
			break;

		}
	}
}
*/

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
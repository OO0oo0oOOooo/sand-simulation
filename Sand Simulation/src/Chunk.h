#pragma once

#include "Cell.h"
#include "Mesh.h"
#include "ChunkData.h"

#include <vector>

enum Space
{
	LocalSpace,
	WorldSpace,
};

class Chunk
{
public:
	Chunk(int x, int y);
	~Chunk();

	void CreateMesh();
	void DrawMesh(Shader* shader);

	inline int GetCellIndex(int x, int y)
	{
		return y * chunkSizeInCells + x;
	}

	inline int GetCellIndex(glm::vec2 index)
	{
		return index.y * chunkSizeInCells + index.x;
	}

	inline Cell GetCell(glm::vec2 position, Space space)
	{
		switch (space)
		{
		case LocalSpace:
			return GetCellLocal(position);
			break;

		case WorldSpace:
			return GetCellFromWorldPos(position);
			break;

		default:
			break;
		}
	}

	inline void SetCell(glm::vec2 position, Cell cell, Space space)
	{
		switch (space)
		{
		case LocalSpace:
			SetCellLocal(position, cell);
			break;

		case WorldSpace:
			SetCellFromWorldPos(position, cell);
			break;

		default:
			break;
		}
	}
	
	glm::vec2 position;
	std::vector<Cell> ChunkData;
	bool dirty;

private:
	Mesh* mesh;

	inline Cell GetCellLocal(glm::vec2 localPos)
	{
		if ((int)localPos.x % 64 == 0 || (int)localPos.y % 64 == 0)
			return ParticleVoid;

		int index = GetCellIndex(localPos.x, localPos.y);

		return ChunkData[index];
	}

	inline void SetCellLocal(glm::vec2 localPos, Cell cell)
	{
		if ((int)localPos.x % 64 == 0 || (int)localPos.y % 64 == 0)
			return;

		int index = GetCellIndex(localPos.x, localPos.y);

		ChunkData[index] = cell;
		ChunkData[index].position = position + localPos;

		Vertex v[4];
		for (int i = 0; i < 4; i++)
		{
			v[i].position = (glm::vec3(position + localPos, 0) + vertexPositions[i]) * (float)cellSize;
			v[i].color = cell.color;
		}

		int baseVertexIndex = index * 4;

		mesh->UploadVBOSubData(v, 4 * sizeof(Vertex), baseVertexIndex * sizeof(Vertex));
	}

	inline Cell GetCellFromWorldPos(glm::vec2 worldPosition)
	{
		glm::vec2 localPos = worldPosition - position;

		if ((int)localPos.x % chunkSizeInCells == 0 || (int)localPos.y % chunkSizeInCells == 0)
			return ParticleVoid;

		int index = GetCellIndex(localPos.x, localPos.y);

		return ChunkData[index];
	}

	inline void SetCellFromWorldPos(glm::vec2 worldPosition, Cell cell)
	{
		glm::vec2 localPos = worldPosition - position;

		if ((int)localPos.x % chunkSizeInCells == 0 || (int)localPos.y % chunkSizeInCells == 0)
			return;

		int index = GetCellIndex(localPos.x, localPos.y);

		ChunkData[index] = cell;
		ChunkData[index].position = worldPosition;

		Vertex v[4];
		for (int i = 0; i < 4; i++)
		{
			v[i].position = (glm::vec3(worldPosition, 0) + vertexPositions[i]) * (float)cellSize;
			v[i].color = cell.color;
		}

		int baseVertexIndex = index * 4;

		mesh->UploadVBOSubData(v, 4 * sizeof(Vertex), baseVertexIndex * sizeof(Vertex));
	}
};

#pragma once

#include "Cell.h"
#include "Mesh.h"
#include "ChunkData.h"

#include <vector>

class Chunk
{
public:
	Chunk(int x, int y);
	~Chunk();

	void CreateMesh();
	void DrawMesh(Shader* shader);

	int GetCellIndex(int x, int y)
	{
		return y * chunkSizeInCells + x;
	}

	inline void SetCell(int x, int y, Cell cell)
	{
		if (x < 0 || x >= chunkSizeInCells || y < 0 || y >= chunkSizeInCells)
			return;

		int index = GetCellIndex(x, y);

		ChunkData[index] = cell;
		ChunkData[index].position = glm::vec2(x, y);
		ChunkData[index].dirty = true;

	}

	glm::vec2 position;

private:
	std::vector<Cell> ChunkData;
	Mesh* mesh;
};
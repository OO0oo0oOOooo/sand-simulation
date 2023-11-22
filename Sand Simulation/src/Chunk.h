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

	inline void SetCell(int x, int y, Cell cell)
	{
		/*if (x < 0 || x >= chunkSizeInCells || y < 0 || y >= chunkSizeInCells)
			return;*/

		ChunkData[y * chunkSizeInCells + x] = cell;
		ChunkData[y * chunkSizeInCells + x].position = glm::vec2(x, y);
		ChunkData[y * chunkSizeInCells + x].dirty = true;

	}

	glm::vec2 position;

private:
	std::vector<Cell> ChunkData;
	Mesh* mesh;
};
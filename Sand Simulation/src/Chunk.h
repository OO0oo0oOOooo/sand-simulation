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

	inline Cell GetCell(int x, int y)
	{
		if (x < 0 || x >= chunkSizeInCells || y < 0 || y >= chunkSizeInCells)
			return ParticleAir;

		int index = GetCellIndex(x, y);

		return ChunkData[index];
	}

	inline void SetCell(int x, int y, Cell cell)
	{
		if (x < 0 || x >= chunkSizeInCells || y < 0 || y >= chunkSizeInCells)
			return;

		int index = GetCellIndex(x, y);
		glm::vec2 pos = {x, y};

		ChunkData[index] = cell;
		ChunkData[index].position = pos;
		//ChunkData[index].dirty = true;

		// I need the chunk offset for this
		Vertex v[4];
		for (int i = 0; i < 4; i++)
		{
			v[i].position = (glm::vec3(position.x + x, position.y + y, 0) + vertexPositions[i]) * (float)cellSize;
			v[i].color = cell.color;
		}

		int baseVertexIndex = index * 4;

		mesh->UploadVBOSubData(v, 4 * sizeof(Vertex), baseVertexIndex * sizeof(Vertex));
	}

	glm::vec2 position;
	std::vector<Cell> ChunkData;
	bool dirty;

private:
	Mesh* mesh;
};


/*
Vertex v[4];

glm::ivec2 pos = grid->DirtyCells[x].position;
Cell& cell = grid->GetCellRefrence(pos.x, pos.y);

for (int i = 0; i < 4; i++)
{
	v[i].position = (glm::vec3(pos.x, pos.y, 0) + vertexPositions[i]) * (float)grid->CellSize;
	v[i].color = cell.color;
}

int baseVertexIndex = (pos.y * grid->GridWidth + pos.x) * 4;

mesh->UploadVBOSubData(v, 4 * sizeof(Vertex), baseVertexIndex * sizeof(Vertex));
*/
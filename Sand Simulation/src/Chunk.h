#pragma once

#include "Cell.h"
#include "Mesh.h"

#include <vector>


class Chunk
{
public:
	Chunk();
	~Chunk();

	void CreateMesh();
	void UpdateMesh();
	void DrawMesh(Shader* shader);

private:
	std::vector<Cell> ChunkData;
	Mesh* mesh;

	int chunkSizeInCells = 64;
	int cellSize = 1;

};

Chunk::Chunk()
{
	ChunkData = std::vector<Cell>(chunkSizeInCells * chunkSizeInCells);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			ChunkData[x + y * chunkSizeInCells] = ParticleAir;
		}
	}
}

Chunk::~Chunk()
{
}
#pragma once

#include "Cell.h"
#include "Mesh.h"

#include <vector>

class Chunk
{
public:
	Chunk(int x, int y);
	~Chunk();

	void CreateMesh();
	void DrawMesh(Shader* shader);

	glm::vec2 position;
private:
	std::vector<Cell> ChunkData;
	Mesh* mesh;

	int chunkSizeInCells = 64;
	int cellSize = 4;

};
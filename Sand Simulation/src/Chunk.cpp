#include "Chunk.h"

#include <iostream>

Chunk::Chunk(int x, int y)
	: position(x, y)
{
	ChunkData = std::vector<Cell>(chunkSizeInCells * chunkSizeInCells);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			ChunkData[x + y * chunkSizeInCells] = ParticleAir;
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
	std::cout << "Chunk: X " << position.x << ", Y " << position.y << std::endl;

	mesh->vertices.resize(chunkSizeInCells * chunkSizeInCells * 4);
	mesh->indices.resize(chunkSizeInCells * chunkSizeInCells * 6);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			int baseVertexIndex = (y * chunkSizeInCells + x) * 4;
			int baseIndexIndex = (y * chunkSizeInCells + x) * 6;
			//Cell& cell = ChunkData[y * chunkSizeInCells + x];

			int newX = x + position.x;
			int newY = y + position.y;

			for (int i = 0; i < 4; i++)
			{
				mesh->vertices[baseVertexIndex + i].position = (glm::vec3(newX, newY, 0) + vertexPositions[i]) * (float)cellSize;
				if ( newX % chunkSizeInCells == 0)
					mesh->vertices[baseVertexIndex + i].color = { 1, 0, 0, 1 };
				else if ( newY % chunkSizeInCells == 0)
					mesh->vertices[baseVertexIndex + i].color = { 0, 1, 0, 1 };
				else
					mesh->vertices[baseVertexIndex + i].color = { 1, 1, 1, 1 };
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


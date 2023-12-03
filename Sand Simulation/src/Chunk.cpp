#include "Chunk.h"

Chunk::Chunk(int x, int y)
	: position(x, y), dirty(false)
{
	ChunkData = std::vector<Cell>(chunkSizeInCells * chunkSizeInCells);

	for (int x = 0; x < chunkSizeInCells; x++)
	{
		for (int y = 0; y < chunkSizeInCells; y++)
		{
			ChunkData[GetCellIndex(x, y)] = ParticleAir;
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
		
		if(ActiveCells[i].x < bounds.min.x && ActiveCells[i].y < bounds.min.y)
			bounds.min = ActiveCells[i];

		if (ActiveCells[i].x > bounds.max.x && ActiveCells[i].y > bounds.max.y)
			bounds.max = ActiveCells[i];

	}

	bounds.size = (bounds.max - bounds.min) + 1;
	bounds.position = bounds.min;
}

void Chunk::UpdateActive()
{
	if(ActiveCells.size() <= 0)
		return;

	RecalculateBounds();
	//ActiveCells.clear();

	if(bounds.size.x <= 0 || bounds.size.y <= 0)
		return;

	// Iterate through all cells in bounds from the bottom up
	// could switch the direction we iterate through on the x to remove the bias
	for (int y = 0; y < bounds.size.y; y++)
	{
		for (int x = 0; x < bounds.size.x; x++)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);
			Cell cell = GetCell(boundsPosition, LocalSpace);
			glm::ivec2 cellPosition = cell.position;

			glm::ivec2 Neighbours[8] = 
			{
				cellPosition + glm::ivec2( 0, -1), // Bot
				cellPosition + glm::ivec2(-1, -1), // Bot Left
				cellPosition + glm::ivec2( 1, -1), // Bot Right
				cellPosition + glm::ivec2(-1,  0), // Left
				cellPosition + glm::ivec2( 1,  0), // Right
				cellPosition + glm::ivec2( 0,  1), // Top
				cellPosition + glm::ivec2(-1,  1), // Top Left
				cellPosition + glm::ivec2( 1,  1), // Top Right
			};

			if(cell.Id == ParticleSand.Id)
			{
				for (int j = 0; j <= 2; j++)
				{
					Cell neighbour;

					if ((Neighbours[j].x - position.x) < 0 || (Neighbours[j].x - position.x) > 63 || (Neighbours[j].y - position.y) < 0 || (Neighbours[j].y - position.y) > 63)
						continue;
					else
						neighbour = GetCell(Neighbours[j], WorldSpace);

					if (neighbour.Id == ParticleAir.Id)
					{
						//if (Neighbours[j].x % 64 == 0 || Neighbours[j].y % 64 == 0)
						//	std::cout << "World" << std::endl; //world->GetChunkFromWorldPos(Neighbours[j])->SetCell(Neighbours[j], ParticleSand, WorldSpace);
						//else
						//{
						SetCell(cellPosition, ParticleAir, WorldSpace);
						SetCell(Neighbours[j], ParticleSand, WorldSpace);

						ActiveCells.push_back(cellPosition - position);
						ActiveCells.push_back(Neighbours[j] - position);
						//}

						break;
					}

				}
			}

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());

		}
	}

}
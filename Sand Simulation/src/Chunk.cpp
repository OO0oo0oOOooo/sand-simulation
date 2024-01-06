#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, int x, int y)
	: position(x, y), dirty(false), world(world)
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

	for (int y = 0; y < bounds.size.y; y++)
	{
		bool alternate = (y % 2 == 0);
		int startX = alternate ? 0 : bounds.size.x - 1;
		int endX = alternate ? bounds.size.x : -1;
		int stepX = alternate ? 1 : -1;

		for (int x = startX; x != endX; x += stepX)
		{
			glm::ivec2 boundsPosition = bounds.position + glm::ivec2(x, y);
			Cell cell = GetCell(boundsPosition, LocalSpace);
			glm::ivec2 cellPosition = cell.position;

			if (cell.Id == ParticleSand.Id)
			{
				for (int j = 0; j <= 2; j++)
				{
					glm::ivec2 neighbourPosition = cellPosition + NeighbourTable[j];
					Cell neighbour = world->GetChunkFromWorldPos(neighbourPosition)->GetCell(neighbourPosition, WorldSpace);

					if (neighbour.Id == ParticleAir.Id)
					{
						Cell particle = ParticleSand;

						SetCell(cell.position, ParticleAir, WorldSpace);
						world->GetChunkFromWorldPos(neighbourPosition)->SetCell(neighbourPosition, particle, WorldSpace);

						break;
					}
				}
			}

			ActiveCells.erase(std::remove(ActiveCells.begin(), ActiveCells.end(), cellPosition - position), ActiveCells.end());
		}
	}
}
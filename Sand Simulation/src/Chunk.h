#pragma once

//#include "glm/glm.hpp"
#include "v2kh.h"

class Element;

#include "Mesh.h"
#include "Time.h"
#include "ChunkData.h"

#include <unordered_map>
#include <iostream>
#include <vector>

class World;

struct Bounds
{
	glm::ivec2 min;
	glm::ivec2 max;

	glm::ivec2 position;
	glm::ivec2 size;
};

const glm::vec3 vertexPositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
};

const unsigned int meshTriangles[] = {
	0, 1, 2,
	2, 1, 3,
};

class Chunk
{
public:
	Chunk(World* world, int x, int y);

	~Chunk()
	{
		delete _mesh;
	}

	void Update();

	void CreateMesh();

	void DrawMesh(Shader* shader)
	{
		_mesh->Draw(shader);
	}

	void UploadMeshData()
	{
		_mesh->UploadVBOData();
		_mesh->UploadIBOData();
	}

	inline int GetIndex(glm::ivec2 index)
	{
		/*if (index.x < 0 || index.x > 63 || index.y < 0 || index.y > 63)
			return -1;*/

		return index.y * chunkSizeInCells + index.x;
	}

	inline Element* GetElementAtLocalPosition(glm::ivec2 pos)
	{
		if (pos.x < 0 || pos.x > chunkSizeInCells - 1 || pos.y < 0 || pos.y > chunkSizeInCells - 1)
			return nullptr;

		return _chunkData[GetIndex(pos)];
	}

	void SetElementAtLocalPosition(glm::ivec2 pos, Element* element);

	void SetElementAtWorldPosition(glm::ivec2 worldPosition, Element* element);

	inline void SetShouldUpdateNextFrame(bool b)
	{
		_shouldUpdateNextFrame = b;
	}

	inline bool GetShouldUpdateNextFrame()
	{
		return _shouldUpdate;
	}

	glm::ivec2 Position;

private:
	std::vector<Element*> _chunkData;
	World* _world;
	Mesh* _mesh;

	bool _shouldUpdate = false;
	bool _shouldUpdateNextFrame = false;

	bool UpdateState()
	{
		_shouldUpdate = _shouldUpdateNextFrame;
		_shouldUpdateNextFrame = false;

		return _shouldUpdate;
	}
};

/*
* Old Chunk class

#include "Cell.h"
#include "Mesh.h"
#include "ChunkData.h"
#include "Time.h"

class World;

#include <vector>
#include <iostream>

struct Bounds
{
	glm::ivec2 min;
	glm::ivec2 max;

	glm::ivec2 position;
	glm::ivec2 size;
};

enum Space
{
	LocalSpace,
	WorldSpace,
};

class Chunk
{
public:
	Chunk(World* world, int x, int y);
	~Chunk();

	void CreateMesh();
	void DrawMesh(Shader* shader);

	void UploadMeshData()
	{
		mesh->UploadVBOData();
		mesh->UploadIBOData();
	}

	void DrawDirtyQuad(Shader* shader)
	{
		if (bounds.size.x <= 0 || bounds.size.y <= 0)
			return;

		std::vector<Vertex> vertices = {
			{{(position.x + bounds.min.x) * cellSize, (position.y + bounds.min.y) * cellSize - 5, 0.2f}, {1.0, 0.2, 0.1, 1}},
			{{(position.x + bounds.max.x) * cellSize + 5, (position.y + bounds.min.y) * cellSize - 5, 0.2f}, {1.0, 0.2, 0.1, 1}},
			{{(position.x + bounds.max.x) * cellSize + 5, (position.y + bounds.max.y) * cellSize + 5, 0.2f}, {1.0, 0.2, 0.1, 1}},
			{{(position.x + bounds.min.x) * cellSize, (position.y + bounds.max.y) * cellSize + 5, 0.2f}, {1.0, 0.2, 0.1, 1}},
		};

		std::vector<unsigned int> indices = {
			0, 1, // Bottom edge
			1, 2, // Right edge
			2, 3, // Top edge
			3, 0  // Left edge
		};

		Mesh squareOutline;
		squareOutline.vertices = vertices;
		squareOutline.indices = indices;
		squareOutline.UploadVBOData();
		squareOutline.UploadIBOData();

		squareOutline.DrawLine(shader);
	}

	inline int GetCellIndex(int x, int y)
	{
		if(x < 0 || x > 64 || y < 0 || y > 64)
			return -1;

		return y * chunkSizeInCells + x;
	}

	inline int GetCellIndex(glm::ivec2 index)
	{
		if (index.x < 0 || index.x > 63 || index.y < 0 || index.y > 63)
			return -1;

		return index.y * chunkSizeInCells + index.x;
	}

	inline Cell& GetCellRefrence(glm::ivec2 worldPosition)
	{
		if (worldPosition.x < 0 || worldPosition.x > worldSizeInCells.x - 1 || worldPosition.y < 0 || worldPosition.y > worldSizeInCells.y - 1)
			throw std::out_of_range("Index out of bounds");

		glm::ivec2 localPos = worldPosition - position;
		int index = GetCellIndex(localPos.x, localPos.y);

		return ChunkData[index];
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
			SetCellWorld(position, cell);
			break;
		}
	}
	
	glm::ivec2 position;
	std::vector<Cell> ChunkData;

	std::vector<glm::ivec2> ActiveCells;
	Bounds bounds;

	void RecalculateBounds();
	void UpdateActive();

	World* world;
	Mesh* mesh;

private:

	void SandUpdate(Cell cell);

	inline Cell GetCellLocal(glm::ivec2 localPos)
	{
		if (localPos.x < 0 || localPos.x > chunkSizeInCells - 1 || localPos.y < 0 || localPos.y > chunkSizeInCells - 1)
			return VOID;

		int index = GetCellIndex(localPos.x, localPos.y);

		return ChunkData[index];
	}

	inline Cell GetCellFromWorldPos(glm::ivec2 worldPosition)
	{
		if (worldPosition.x < 0 || worldPosition.x > worldSizeInCells.x - 1 || worldPosition.y < 0 || worldPosition.y > worldSizeInCells.y - 1)
			return VOID;

		glm::ivec2 localPos = worldPosition - position;
		int index = GetCellIndex(localPos.x, localPos.y);

		return ChunkData[index];
	}

	inline void SetCellLocal(glm::vec2 localPos, Cell cell)
	{
		if (localPos.x < 0 || localPos.x > chunkSizeInCells - 1 || localPos.y < 0 || localPos.y > chunkSizeInCells - 1)
			return;
	
		int index = GetCellIndex(localPos.x, localPos.y);
	
		ChunkData[index] = cell;
		ChunkData[index].position = { position.x + localPos.x, position.y + localPos.y };
	
		if (cell.Id == AIR.Id)
			return;
	
		ActiveCells.push_back(localPos);
	
		int baseVertexIndex = index * 4;
	
		for (int i = 0; i < 4; i++)
		{
			Vertex v;
	
			v.position = (glm::vec3(localPos, 0) + vertexPositions[i]) * (float)cellSize;
			v.color = cell.color;
	
			mesh->vertices[baseVertexIndex + i] = v;
		}
	}

	inline void SetCellWorld(glm::vec2 worldPosition, Cell cell)
	{
		if (worldPosition.x < 0 || worldPosition.x > worldSizeInCells.x - 1 || worldPosition.y < 0 || worldPosition.y > worldSizeInCells.y - 1)
			return;
	
		glm::ivec2 localPos = { worldPosition.x - position.x, worldPosition.y - position.y};
	
		int index = GetCellIndex(localPos.x, localPos.y);
	
		ChunkData[index] = cell;
		ChunkData[index].position = worldPosition;
	
		if (cell.Id != AIR.Id)
		{
			ActiveCells.push_back(localPos);
		}
	
		int baseVertexIndex = index * 4;
	
		for (int i = 0; i < 4; i++)
		{
			Vertex v;
	
			v.position = (glm::vec3(worldPosition, 0) + vertexPositions[i]) * (float)cellSize;
			v.color = cell.color;
	
			mesh->vertices[baseVertexIndex + i] = v;
		}
	}
};

*/
#pragma once

#include "ctpl/ctpl_stl.h"
#include "Chunk.h"

class Element;

class World
{
public:
	World(ctpl::thread_pool* pool) : _threadPool(pool)
	{
		for (int x = 0; x < numChunksWidth; x++)
		{
			for (int y = 0; y < numChunksHeight; y++)
			{
				_chunks[glm::vec2(x, y)] = new Chunk(this, x * 64, y * 64);
			}
		}


		_debugBordersMesh = new Mesh();
		DebugDrawInit();
	}
	
	~World()
	{
		for (auto& chunk : _chunks)
		{
			delete chunk.second;
		}

		delete _debugBordersMesh;
	}

	void Update(Shader* shader);

	inline void Draw(Shader* shader)
	{
		for (auto& chunk : _chunks)
		{
			chunk.second->UploadMeshData();
			chunk.second->DrawMesh(shader);
		}
	}

	inline void DebugDrawInit()
	{
		int padding = 1;

		for (int x = 0; x < numChunksWidth; x++)
		{
			for (int y = 0; y < numChunksHeight; y++)
			{
				/*Chunk* chunk = _chunks[glm::vec2(x, y)];
				glm::vec2 pos = chunk->Position;

				if (chunk == nullptr)
					return;*/

				std::cout << x << ", " << y << std::endl;

				std::vector<Vertex> vertices = {
					{ { (x * chunkSizeInCells * cellSize) + padding,			(y * chunkSizeInCells * cellSize) + padding,			0.2f },		{1.0, 1.0, 1.0, 0.25} },
					{ { (x * chunkSizeInCells * cellSize) + padding,			(y * chunkSizeInCells * cellSize) + (64 * cellSize),	0.2f,},		{1.0, 1.0, 1.0, 0.25} },
					{ { (x * chunkSizeInCells * cellSize) + (64 * cellSize),	(y * chunkSizeInCells * cellSize) + (64 * cellSize),	0.2f },		{1.0, 1.0, 1.0, 0.25} },
					{ { (x * chunkSizeInCells * cellSize) + (64 * cellSize),	(y * chunkSizeInCells * cellSize) + padding,			0.2f },		{1.0, 1.0, 1.0, 0.25} },
				};

				std::vector<unsigned int> indices = {
					0, 1, // Bottom edge
					1, 2, // Right edge
					2, 3, // Top edge
					3, 0  // Left edge
				};

				for (int i = 0; i < 8; i++)
				{
					_debugBordersMesh->indices.push_back(indices[i] + _debugBordersMesh->vertices.size());
				}

				for (int i = 0; i < 4; i++)
				{
					_debugBordersMesh->vertices.push_back(vertices[i]);
				}

				
			}
		}

		_debugBordersMesh->UploadVBOData();
		_debugBordersMesh->UploadIBOData();
	}

	inline void DebugDraw(Shader* shader)
	{
		_debugBordersMesh->DrawLine(shader);
	}

	inline glm::ivec2 PixelToCellPos(glm::vec2 position)
	{
		return glm::ivec2(position / glm::vec2(cellSize, cellSize));
	}

	inline Chunk* GetChunkFromWorldPos(glm::ivec2 position)
	{
		if (position.x < 0 || position.x > worldSizeInCells.x - 1 || position.y < 0 || position.y > worldSizeInCells.y - 1)
			return nullptr;

		// Use map.find() to check if the chunk exists
		glm::ivec2 chunkPos = { ((int)position.x / chunkSizeInCells), ((int)position.y / chunkSizeInCells) };
		return _chunks[chunkPos];
	}

	inline Element* GetElementAtWorldPos(glm::ivec2 position)
	{
		if (position.x < 0 || position.x > worldSizeInCells.x - 1 || position.y < 0 || position.y > worldSizeInCells.y - 1)
			return nullptr;

		Chunk* chunk = GetChunkFromWorldPos(position);

		if (chunk == nullptr)
			return nullptr;

		glm::vec2 localPos = glm::vec2(position - chunk->Position);

		return chunk->GetElementAtLocalPosition(localPos);
	}

	inline void SetElementAtWorldPos(glm::ivec2 position, Element* element)
	{
		if (position.x < 0 || position.x > worldSizeInCells.x - 1 || position.y < 0 || position.y > worldSizeInCells.y - 1)
			return;

		Chunk* chunk = GetChunkFromWorldPos(position);
		glm::vec2 localPos = glm::vec2(position - chunk->Position);

		chunk->SetElementAtLocalPosition(localPos, element);
	}

	void EditElementAtPixel(glm::vec2 position, int element);

	void MoveElement(glm::ivec2 from, glm::ivec2 to);

	void SwapElements(glm::ivec2 pos1, glm::ivec2 pos2);

private:

	ctpl::thread_pool* _threadPool;
	std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> _chunks;


	Mesh* _debugBordersMesh;
};
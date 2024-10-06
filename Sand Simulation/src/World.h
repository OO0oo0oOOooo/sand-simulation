#pragma once

#include "ctpl/ctpl_stl.h"
#include "Chunk.h"

class Element;

class World
{
public:
	World();
	~World();

	void Update(Shader* shader);

	inline void Draw(Shader* shader)
	{
		for (int x = 0; x < numChunksWidth; x++)
		{
			for (int y = 0; y < numChunksHeight; y++)
			{
				m_Chunks[x][y]->UploadMeshData();
				m_Chunks[x][y]->DrawMesh(shader);
			}
		}

		//for (auto& chunk : _chunks)
		//{
		//	chunk.second->UploadMeshData();
		//	chunk.second->DrawMesh(shader);
		//}
	}

	inline void DebugDrawInit()
	{
		m_DebugBordersMesh->Clear();
		int padding = 1;

		for (int x = 0; x < numChunksWidth; x++)
		{
			for (int y = 0; y < numChunksHeight; y++)
			{
				//Chunk* chunk = _chunks[glm::vec2(x, y)];
				Chunk* chunk = m_Chunks[x][y];

				if (chunk == nullptr)
					return;

				if(!chunk->GetShouldUpdateNextFrame())
					continue;

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
					m_DebugBordersMesh->indices.push_back(indices[i] + m_DebugBordersMesh->vertices.size());
				}

				for (int i = 0; i < 4; i++)
				{
					m_DebugBordersMesh->vertices.push_back(vertices[i]);
				}

				
			}
		}

		m_DebugBordersMesh->UploadVBOData();
		m_DebugBordersMesh->UploadIBOData();
	}

	inline void DebugDraw(Shader* shader)
	{
		m_DebugBordersMesh->DrawLine(shader);
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
		glm::ivec2 chunkPos = { (position.x / chunkSizeInCells), (position.y / chunkSizeInCells) };

		//return _chunks[chunkPos];
		return m_Chunks[chunkPos.x][chunkPos.y];
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

	ctpl::thread_pool* m_ThreadPool;
	//std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> _chunks;
	std::vector<std::vector<Chunk*>> m_Chunks;

	Mesh* m_DebugBordersMesh;
};
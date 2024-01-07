#pragma once

#include "glm/glm.hpp"

#include "Chunk.h"
#include <unordered_map>

#include "ctpl/ctpl_stl.h"

class World
{
public:
	World(ctpl::thread_pool* pool);
	~World();

	void Render(Shader* shader);

    void Update();
	void UpdateChunks();
	void UpdateCells(Chunk* chunk);

	void DrawChunkBorders();

	inline glm::ivec2 GetChunkFromPixelPos(glm::vec2 position)
	{
		//glm::vec2 adjustedChunkSize = glm::vec2(chunkSizeInCells * cellSize * aspectRatio.x, chunkSizeInCells * cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / cellSize));
		int y = static_cast<int>(floor(position.y / cellSize));
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromPixelPos(glm::vec2 position)
	{
		//glm::vec2 adjustedCellSize = glm::vec2(cellSize * aspectRatio.x, cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / cellSize)) % chunkSizeInCells;
		int y = static_cast<int>(floor(position.y / cellSize)) % chunkSizeInCells;
		return glm::ivec2(x, y);
	}


	inline Chunk* GetChunkFromWorldPos(glm::ivec2 position)
	{
		glm::ivec2 chunkPos = { ((int)position.x / chunkSizeInCells), ((int)position.y / chunkSizeInCells) };
		return chunks[chunkPos];
	}

	inline Cell GetCellFromWorldPos(glm::ivec2 position)
	{
		Chunk* chunk = GetChunkFromWorldPos(position);
		glm::vec2 localPos = glm::vec2(position - chunk->position);

		return chunk->GetCell(localPos, LocalSpace);
	}

	inline void EditCell(glm::vec2 position, Cell cell)
	{
		if(position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080)
			return;

		glm::ivec2 cellPos = (position / glm::vec2(5, 5));
		Chunk* chunk = GetChunkFromWorldPos(cellPos);

		chunk->SetCell(cellPos, cell, WorldSpace);
	}

	std::vector<Cell> dirtyCells;
	ctpl::thread_pool* threadPool;

private:
	struct KeyHash {
		std::size_t operator()(const glm::ivec2& k) const {
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}
	};

	struct KeyEqual {
		bool operator()(const glm::ivec2& lhs, const glm::ivec2& rhs) const {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};

	std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> chunks;
	//glm::vec2 aspectRatio = glm::vec2(1.0f, 1.0f);
};
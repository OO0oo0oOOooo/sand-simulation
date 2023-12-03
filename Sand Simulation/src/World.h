#pragma once

#include "glm/glm.hpp"

#include "Chunk.h"
#include <unordered_map>

class World
{
public:
	World();
	~World();

	void Render(Shader* shader);

    void Update(float deltaTime);
	void UpdateChunks();
	void UpdateCells(Chunk* chunk);

	////Normalized position
	//inline glm::ivec2 GetChunkFromNormalizedPos(glm::vec2 normalizedPos)
	//{
	//	int x = (int)(normalizedPos.x * numChunksWidth);
	//	int y = (int)(normalizedPos.y * numChunksHeight);
	//	return glm::ivec2(x, y);
	//}

	//inline glm::ivec2 GetCellFromNormalizedPos(glm::vec2 normalizedPos)
	//{
	//	glm::ivec2 chunkPos = GetChunkFromNormalizedPos(normalizedPos);
	//	glm::vec2 posInChunk = glm::vec2(normalizedPos.x * numChunksWidth - chunkPos.x, normalizedPos.y * numChunksHeight - chunkPos.y);
	//	glm::ivec2 cellPos = glm::ivec2((int)(posInChunk.x * chunkSizeInCells), (int)(posInChunk.y * chunkSizeInCells));
	//	return cellPos;
	//}

	//// Raw position
	/*inline glm::ivec2 GetChunkFromPos(glm::vec2 position)
	{
		int x = floor(position.x / (chunkSizeInCells * cellSize));
		int y = floor(position.y / (chunkSizeInCells * cellSize));
		return glm::ivec2(x, y);
	}
	
	inline glm::ivec2 GetCellFromPos(glm::vec2 position)
	{
		int x = static_cast<int>(floor(position.x / cellSize)) % chunkSizeInCells;
		int y = static_cast<int>(floor(position.y / cellSize)) % chunkSizeInCells;
		return glm::ivec2(x, y);
	}*/


	inline glm::ivec2 GetChunkFromPixelPos(glm::vec2 position)
	{
		glm::vec2 adjustedChunkSize = glm::vec2(chunkSizeInCells * cellSize * aspectRatio.x, chunkSizeInCells * cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / adjustedChunkSize.x));
		int y = static_cast<int>(floor(position.y / adjustedChunkSize.y));
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromPixelPos(glm::vec2 position)
	{
		glm::vec2 adjustedCellSize = glm::vec2(cellSize * aspectRatio.x, cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / adjustedCellSize.x)) % chunkSizeInCells;
		int y = static_cast<int>(floor(position.y / adjustedCellSize.y)) % chunkSizeInCells;
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
		if(position.x < 0 || position.x > 1280 || position.y < 0 || position.y > 720)
			return;

		glm::ivec2 cellPos = (position / glm::vec2(4, 4));
		Chunk* chunk = GetChunkFromWorldPos(cellPos);

		chunk->SetCell(cellPos, cell, WorldSpace);
		//dirtyCells.push_back(chunk->GetCell(cellPos, WorldSpace));
	}

	std::vector<Cell> dirtyCells;

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
	glm::vec2 aspectRatio = glm::vec2(1.0f, 1.0f);
};
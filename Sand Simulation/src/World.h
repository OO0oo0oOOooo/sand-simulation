#pragma once

#include "glm/glm.hpp"

#include "Chunk.h"
#include <unordered_map>
#include <iostream>

class World
{
public:
	World();
	~World();

	void Render(Shader* shader);

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

	// 
	inline glm::ivec2 GetChunkFromPos(glm::vec2 position, glm::vec2 aspectRatio)
	{
		// Adjust the chunk size based on the aspect ratio
		glm::vec2 adjustedChunkSize = glm::vec2(chunkSizeInCells * cellSize * aspectRatio.x, chunkSizeInCells * cellSize * aspectRatio.y);

		int x = floor(position.x / adjustedChunkSize.x);
		int y = floor(position.y / adjustedChunkSize.y);
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromPos(glm::vec2 position, glm::vec2 aspectRatio)
	{
		// Adjust the cell size based on the aspect ratio
		glm::vec2 adjustedCellSize = glm::vec2(cellSize * aspectRatio.x, cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / adjustedCellSize.x)) % chunkSizeInCells;
		int y = static_cast<int>(floor(position.y / adjustedCellSize.y)) % chunkSizeInCells;
		return glm::ivec2(x, y);
	}

	inline void EditCell(glm::vec2 position, glm::vec2 aspectRatio, Cell cell)
	{
		glm::ivec2 chunkPos = GetChunkFromPos(position, aspectRatio);
		glm::ivec2 cellPos = GetCellFromPos(position, aspectRatio);

		Chunk* chunk = chunks[chunkPos];
		chunk->SetCell(cellPos.x, cellPos.y, cell);
	}

private:
	struct KeyHash {
		std::size_t operator()(const glm::ivec2& k) const {
			return std::hash<float>()(k.x) ^ std::hash<float>()(k.y);
		}
	};

	struct KeyEqual {
		bool operator()(const glm::ivec2& lhs, const glm::ivec2& rhs) const {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};

	std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> chunks;
};
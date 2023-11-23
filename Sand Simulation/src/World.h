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

	//inline glm::ivec2 GetChunkFromNormalizedPos(glm::vec2 normalizedPos)
	//{
	//	int x = (int)(normalizedPos.x * numChunksWidth);
	//	int y = (int)(normalizedPos.y * numChunksHeight);
	//	return glm::ivec2(x, y);
	//}

	//inline glm::ivec2 GetCellFromNormalizedPos(glm::vec2 normalizedPos)
	//{
	//	// Calculate the chunk position
	//	glm::ivec2 chunkPos = glm::ivec2(normalizedPos.x * numChunksWidth, normalizedPos.y * numChunksHeight);

	//	// Calculate the position within the chunk
	//	glm::vec2 posInChunk = glm::vec2(normalizedPos.x * numChunksWidth - chunkPos.x, normalizedPos.y * numChunksHeight - chunkPos.y);
	//	glm::ivec2 cellPos = glm::ivec2(posInChunk.x * chunkSizeInCells, posInChunk.y * chunkSizeInCells);

	//	return cellPos;
	//}

	inline glm::ivec2 GetChunkFromNormalizedPos(glm::vec2 normalizedPos)
	{
		int x = (int)(normalizedPos.x * numChunksWidth);
		int y = (int)(normalizedPos.y * numChunksHeight);
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromNormalizedPos(glm::vec2 normalizedPos)
	{
		// Calculate the chunk position
		glm::ivec2 chunkPos = GetChunkFromNormalizedPos(normalizedPos);

		// Calculate the position within the chunk
		glm::vec2 posInChunk = glm::vec2(normalizedPos.x * numChunksWidth - chunkPos.x, normalizedPos.y * numChunksHeight - chunkPos.y);
		glm::ivec2 cellPos = glm::ivec2((int)(posInChunk.x * chunkSizeInCells), (int)(posInChunk.y * chunkSizeInCells));

		return cellPos;
	}


	/*inline glm::ivec2 GetChunkFromPos(glm::vec2 normalizedPosition)
	{
		int x = floor(normalizedPosition.x / (chunkSizeInCells * normalizedCellSize));
		int y = floor(normalizedPosition.y / (chunkSizeInCells * normalizedCellSize));
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromPos(glm::vec2 normalizedPosition)
	{
		int x = static_cast<int>(floor(normalizedPosition.x / normalizedCellSize)) % chunkSizeInCells;
		int y = static_cast<int>(floor(normalizedPosition.y / normalizedCellSize)) % chunkSizeInCells;
		return glm::ivec2(x, y);
	}*/

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

	inline void EditCell(glm::vec2 position, Cell cell)
	{
		glm::ivec2 chunkIndex = GetChunkFromNormalizedPos(position);
		glm::ivec2 cellPos = GetCellFromNormalizedPos(position);

		Chunk* chunk = chunks[chunkIndex];
		chunk->SetCell(cellPos.x, cellPos.y, cell);

		chunk->CreateMesh();
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
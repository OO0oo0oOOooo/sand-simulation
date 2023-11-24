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
	//inline glm::ivec2 GetChunkFromPos(glm::vec2 position)
	//{
	//	int x = floor(position.x / (chunkSizeInCells * cellSize));
	//	int y = floor(position.y / (chunkSizeInCells * cellSize));
	//	return glm::ivec2(x, y);
	//}

	//inline glm::ivec2 GetCellFromPos(glm::vec2 position)
	//{
	//	int x = static_cast<int>(floor(position.x / cellSize)) % chunkSizeInCells;
	//	int y = static_cast<int>(floor(position.y / cellSize)) % chunkSizeInCells;
	//	return glm::ivec2(x, y);
	//}

	//inline glm::ivec2 GetChunkFromPos(glm::vec2 position, float aspectRatio)
	//{
	//	// Adjust the position based on the aspect ratio
	//	glm::vec2 adjustedPos = position * glm::vec2(aspectRatio, 1.0f);

	//	int x = floor(adjustedPos.x / (chunkSizeInCells * cellSize));
	//	int y = floor(adjustedPos.y / (chunkSizeInCells * cellSize));
	//	return glm::ivec2(x, y);
	//}

	//inline glm::ivec2 GetCellFromPos(glm::vec2 position, float aspectRatio)
	//{
	//	// Adjust the position based on the aspect ratio
	//	glm::vec2 adjustedPos = position * glm::vec2(aspectRatio, 1.0f);

	//	int x = static_cast<int>(floor(adjustedPos.x / cellSize)) % chunkSizeInCells;
	//	int y = static_cast<int>(floor(adjustedPos.y / cellSize)) % chunkSizeInCells;
	//	return glm::ivec2(x, y);
	//}

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

	/*glm::ivec2 WorldToChunkSpace(glm::vec2 worldPos, glm::vec2 chunkSize)
	{
		return glm::floor(worldPos / chunkSize);
	}

	glm::ivec2 ChunkToCellSpace(glm::vec2 chunkPos, glm::vec2 cellSize)
	{
		return glm::floor(chunkPos / cellSize);
	}*/

	inline void EditCell(glm::vec2 worldPosition, glm::vec2 aspectRatio, Cell cell)
	{
		//glm::ivec2 chunkPos = WorldToChunkSpace(worldPosition, {64, 64});
		//glm::ivec2 cellPos = ChunkToCellSpace(chunkPos, {4, 4});

		glm::ivec2 chunkPos = GetChunkFromPos(worldPosition, aspectRatio);
		glm::ivec2 cellPos = GetCellFromPos(worldPosition, aspectRatio);

		std::cout << "World: " << worldPosition.x << ", " << worldPosition.y << std::endl;
		std::cout << "Chunk: " << chunkPos.x << ", " << chunkPos.y << std::endl;
		std::cout << "Cell: " << cellPos.x << ", " << cellPos.y << std::endl;

		Chunk* chunk = chunks[chunkPos];
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
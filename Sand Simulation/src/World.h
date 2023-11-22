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

	inline glm::ivec2 GetChunkFromNormalizedPos(glm::vec2 normalizedPos)
	{
		int x = (int)(normalizedPos.x * numChunksWidth);
		int y = (int)(normalizedPos.y * numChunksHeight);
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 GetCellFromNormalizedPos(glm::vec2 normalizedPos)
	{
		int x = (int)(normalizedPos.x * chunkSizeInCells);
		int y = (int)(normalizedPos.y * chunkSizeInCells);
		return glm::ivec2(x, y);
	}

	inline Chunk* GetChunk(glm::vec2 chunkPos)
	{
		return chunks[chunkPos];
	}

	inline void EditCell(glm::vec2 normalizedPosition, Cell cell)
	{
		glm::ivec2 chunkIndex = GetChunkFromNormalizedPos(normalizedPosition);
		glm::ivec2 cellPos = GetCellFromNormalizedPos(normalizedPosition);

		std::cout << "Chunk Index: " << chunkIndex.x << ", " << chunkIndex.y << std::endl;
		std::cout << "Cell Index: " << cellPos.x << ", " << cellPos.y << std::endl;

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
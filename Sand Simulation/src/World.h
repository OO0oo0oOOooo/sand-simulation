#pragma once

#include "glm/glm.hpp"

#include "Chunk.h"
#include <unordered_map>
#include <unordered_set>

#include "ctpl/ctpl_stl.h"

#include "ElementTypes/Sand.h"

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

class World
{
public:
	World(ctpl::thread_pool* pool);
	~World();

	//void DrawChunkBorders(Shader* shader);

    void Update(Shader* shader);

	inline void Draw(Shader* shader)
	{
		for (auto& chunk : _chunks)
		{
			chunk.second->UploadMeshData();
			chunk.second->DrawMesh(shader);
		}
	}

	inline glm::ivec2 GetChunkFromPixelPos(glm::vec2 position)
	{
		//glm::vec2 adjustedChunkSize = glm::vec2(chunkSizeInCells * cellSize * aspectRatio.x, chunkSizeInCells * cellSize * aspectRatio.y);

		int x = static_cast<int>(floor(position.x / cellSize));
		int y = static_cast<int>(floor(position.y / cellSize));
		return glm::ivec2(x, y);
	}

	inline glm::ivec2 PixelToCellPos(glm::vec2 position)
	{
		return glm::ivec2(position / glm::vec2(5, 5));
	}

	inline Chunk* GetChunkFromWorldPos(glm::ivec2 position)
	{
		glm::ivec2 chunkPos = { ((int)position.x / chunkSizeInCells), ((int)position.y / chunkSizeInCells) };
		return _chunks[chunkPos];
	}

	inline Element GetCellFromWorldPos(glm::ivec2 position)
	{
		Chunk* chunk = GetChunkFromWorldPos(position);
		glm::vec2 localPos = glm::vec2(position - chunk->Position);

		return chunk->GetElementAtLocalPosition(localPos);
	}

	inline void EditCell(glm::vec2 position, int elementID)
	{
		if(position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080)
			return;

		glm::ivec2 cellPos = PixelToCellPos(position);
		Chunk* chunk = GetChunkFromWorldPos(cellPos);

		Sand sand = { cellPos };

		chunk->SetElementAtWorldPosition(cellPos, sand);
	}

	

	std::unordered_set<Chunk*> ChunksToUpdate;

private:
	
	ctpl::thread_pool* _threadPool;
	std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> _chunks;
};
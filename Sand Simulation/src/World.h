#pragma once

#include "glm/glm.hpp"

#include "Chunk.h"
#include <unordered_map>
#include <unordered_set>

#include "ctpl/ctpl_stl.h"

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

    void Update(Shader* shader);

	inline void Draw(Shader* shader)
	{
		for (auto& chunk : _chunks)
		{
			chunk.second->UploadMeshData();
			chunk.second->DrawMesh(shader);
		}
	}

	//inline glm::ivec2 PixelToChunkPos(glm::vec2 position)
	//{
	//	int x = static_cast<int>(floor(position.x / cellSize));
	//	int y = static_cast<int>(floor(position.y / cellSize));
	//	return glm::ivec2(x, y);
	//}

	inline glm::ivec2 PixelToCellPos(glm::vec2 position)
	{
		return glm::ivec2(position / glm::vec2(5, 5));
	}

	// Use map.find() to check if the chunk exists
	inline Chunk* GetChunkFromWorldPos(glm::ivec2 position)
	{
		if (position.x < 0 || position.x > worldSizeInCells.x - 1 || position.y < 0 || position.y > worldSizeInCells.y - 1)
			return nullptr;

		glm::ivec2 chunkPos = { ((int)position.x / chunkSizeInCells), ((int)position.y / chunkSizeInCells) };
		return _chunks[chunkPos];
	}


	inline Element GetElementAtWorldPos(glm::ivec2 position)
	{
		if (position.x < 0 || position.x > worldSizeInCells.x - 1 || position.y < 0 || position.y > worldSizeInCells.y - 1)
			return Elements::empty;

		Chunk* chunk = GetChunkFromWorldPos(position);

		if (chunk == nullptr)
			return Elements::empty;

		glm::vec2 localPos = glm::vec2(position - chunk->Position);

		return chunk->GetElementAtLocalPosition(localPos);
	}

	inline void SetElementAtWorldPos(glm::ivec2 position, Element element)
	{
		Chunk* chunk = GetChunkFromWorldPos(position);
		glm::vec2 localPos = glm::vec2(position - chunk->Position);

		chunk->SetElementAtLocalPosition(localPos, element);
	}






	inline void EditElementAtPixel(glm::vec2 position, int element)
	{
		if(position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080)
			return;

		glm::ivec2 cellPos = PixelToCellPos(position);
		Chunk* chunk = GetChunkFromWorldPos(cellPos);

		chunk->SetElementAtWorldPosition(cellPos, Elements::sand);
	}

	//std::unordered_set<Chunk*> ChunksToUpdate;

private:
	
	ctpl::thread_pool* _threadPool;
	std::unordered_map<glm::ivec2, Chunk*, KeyHash, KeyEqual> _chunks;
};
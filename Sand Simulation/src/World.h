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

private:
	struct KeyHash {
		std::size_t operator()(const glm::vec2& k) const {
			return std::hash<float>()(k.x) ^ std::hash<float>()(k.y);
		}
	};

	struct KeyEqual {
		bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
	};

	std::unordered_map<glm::vec2, Chunk*, KeyHash, KeyEqual> chunks;
	//std::vector<Chunk> chunks;

	int numChunksWidth = 20;
	int numChunksHeight = 11;
};
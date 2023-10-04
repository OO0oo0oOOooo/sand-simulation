#pragma once

#include <vector>

#include <glm/glm.hpp>


struct TerrainData {
	unsigned char type;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

class Grid
{
public:
	Grid();
	~Grid();

	void UpdateArrays();

	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;
	unsigned int gridResolution = 32;

	unsigned int tileSize = windowWidth / gridResolution;
	unsigned int tilesX = windowWidth / tileSize;
	unsigned int tilesY = windowHeight / tileSize;

	std::vector<std::vector<TerrainData>> TerrainMap;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	inline glm::ivec2 GetTileIndexFromPos(glm::vec2 pos)
	{
		return glm::ivec2((int)(pos.x / tileSize), (int)(pos.y / tileSize));
	}
};



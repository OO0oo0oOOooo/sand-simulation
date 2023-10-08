#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>

#include "Shader.h"
#include "vertexBuffer.h"
#include "IndexBuffer.h"

struct TerrainData {
	unsigned char type;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void AddVertex(Vertex vertex);
	void AddIndex(unsigned int index);

	void GenerateTerrainMap();
	void UpdateBuffers();

	void Clear() const;
	void Draw();

	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;
	unsigned int gridResolution = 64;

	unsigned int tileSize = windowWidth / gridResolution;
	unsigned int tilesX = windowWidth / tileSize;
	unsigned int tilesY = windowHeight / tileSize;

	inline glm::ivec2 GetTileIndexFromPos(glm::vec2 pos)
	{
		return glm::ivec2((int)(pos.x / tileSize), (int)(pos.y / tileSize));
	}

	std::vector<std::vector<TerrainData>> TerrainMap;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	
private:
	unsigned int* vao;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;

};
#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>


#include "Shader.h"
#include "vertexBuffer.h"
#include "IndexBuffer.h"

#include "ParticleData.h"
#include "Grid.h"

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

	void UpdateBuffers(Grid* grid);

	void Clear() const;
	void Draw();

	unsigned int windowWidth =    1280;
	unsigned int windowHeight =   720;
	unsigned int gridResolution = 64;

	unsigned int tileSize = windowWidth / gridResolution;
	unsigned int tilesX =   windowWidth / tileSize;
	unsigned int tilesY =   windowHeight / tileSize;
	
private:
	unsigned int* vao;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;
};
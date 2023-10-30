#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>

#include "Shader.h"
#include "vertexBuffer.h"
#include "IndexBuffer.h"

#include "Cell.h"
#include "Grid.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

class Renderer
{
public:
	Renderer(int windowWidth, int windowHeight);
	~Renderer();

	void InitBuffers(Grid* grid);
	void UpdateBuffers(Grid* grid);
	void UpdateDirtyBuffers(Grid* grid);

	void Clear() const;
	void Draw();

	void SetShaderUniforms(float windowWidth, float windowHeight);
	
private:
	unsigned int* vao;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Shader* shader;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};
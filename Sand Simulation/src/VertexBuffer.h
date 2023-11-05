#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	// glm::vec2 uv;
};

class VertexBuffer
{
public:
	VertexBuffer(std::vector<Vertex>& vertices);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(std::vector<Vertex>& vertices);
	void UpdateSubData(const void* data, unsigned int size, int offset);

private:
	unsigned int m_RendererID;
};
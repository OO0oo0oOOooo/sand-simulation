#pragma once

#include "glad/glad.h"
#include "Vertex.h"
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer(std::vector<Vertex>& vertices);
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(std::vector<Vertex>& vertices);
	void UpdateSubData(const void* data, unsigned int size, int offset);

private:
	unsigned int m_RendererID;
};

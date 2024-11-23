#pragma once

#include "GL/glew.h"
#include <vector>

class IndexBuffer
{
public:
	IndexBuffer(std::vector<unsigned int>& indices);
	IndexBuffer();
	~IndexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(std::vector<unsigned int>& indices);
	void UpdateSubData(const void* data, unsigned int size, int offset);

	unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
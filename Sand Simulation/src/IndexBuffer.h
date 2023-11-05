#pragma once

#include "GL/glew.h"
#include <vector>

class IndexBuffer
{
public:
	IndexBuffer(std::vector<unsigned int>& indices);
	~IndexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(std::vector<unsigned int>& indices);

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
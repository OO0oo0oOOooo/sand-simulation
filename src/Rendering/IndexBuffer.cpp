#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int>& indices)
	: m_Count(indices.size())
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
	: m_Count(0)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::UpdateData(std::vector<unsigned int>& indices)
{
	m_Count = indices.size(); //indices.size() * sizeof(unsigned int);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

// HAVENT TESTED THIS FUNCTION
// this should be the same as the UpdateData function but opengl recommends using this function for updating data
void IndexBuffer::UpdateSubData(const void* data, unsigned int size, int offset)
{
	m_Count = size;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(const void* data, unsigned int size);
	void UpdateDirty(const void* data, unsigned int size, int offset);

private:
	unsigned int m_RendererID;
};
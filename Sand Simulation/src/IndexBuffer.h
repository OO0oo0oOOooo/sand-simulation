#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

	void UpdateData(const unsigned int* data, unsigned int count);

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
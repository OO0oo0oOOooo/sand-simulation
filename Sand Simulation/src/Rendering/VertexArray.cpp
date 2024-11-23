#include "VertexArray.h"

VertexArray::VertexArray()
{
    //glGenVertexArrays(1, m_RendererID);

    m_RendererID = new unsigned int;
    m_VertexBuffer = new VertexBuffer();
    m_IndexBuffer = new IndexBuffer();

    glGenVertexArrays(1, m_RendererID);
    glBindVertexArray(*m_RendererID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    glEnableVertexAttribArray(1);
}

VertexArray::~VertexArray()
{
    delete m_RendererID;
    delete m_VertexBuffer;
    delete m_IndexBuffer;

    glDeleteVertexArrays(1, m_RendererID);
}

void VertexArray::Bind()
{
    glBindVertexArray(*m_RendererID);
    //m_VertexBuffer->Bind();
    m_IndexBuffer->Bind();
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
    //m_VertexBuffer->Unbind();
    m_IndexBuffer->Unbind();
}

void VertexArray::UploadBufferData(std::vector<Vertex> verts, std::vector<unsigned int> indices)
{
    m_VertexBuffer->UpdateData(verts);
    m_IndexBuffer->UpdateData(indices);
}

void VertexArray::UploadBufferSubData(std::vector<Vertex> verts, std::vector<unsigned int> indices, int offsetV, int offsetI)
{
	m_VertexBuffer->UpdateSubData(verts.data(), verts.size() * sizeof(Vertex), offsetV);
	m_IndexBuffer->UpdateSubData(indices.data(), indices.size() * sizeof(unsigned int), offsetI);
}

void VertexArray::SetVertexBuffer(VertexBuffer* vb)
{
    glBindVertexArray(*m_RendererID);
    vb->Bind();

    m_VertexBuffer = vb;
}

void VertexArray::SetIndexBuffer(IndexBuffer* ib)
{
    glBindVertexArray(*m_RendererID);
    ib->Bind();

    m_IndexBuffer = ib;
}

VertexBuffer* VertexArray::GetVertexBuffer()
{
    return m_VertexBuffer;
}

IndexBuffer* VertexArray::GetIndexBuffer()
{
    return m_IndexBuffer;
}

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void UploadBufferData(std::vector<Vertex> verts, std::vector<unsigned int> indices);

    void SetVertexBuffer(VertexBuffer* vb);
    void SetIndexBuffer(IndexBuffer* ib);

    IndexBuffer* GetIndexBuffer();
    VertexBuffer* GetVertexBuffer();

private:
    unsigned int* m_RendererID;
    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
};
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <vector>
#include <string>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void Draw(Shader* shader) const noexcept
    {
        glBindVertexArray(*vao);
        shader->Bind();
        ib->Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    void UploadIBOData() noexcept
	{
		ib->UpdateData(indices);
	}

    void UploadVBOData() noexcept
    {
        vb->UpdateData(vertices);
    }

    void UploadVBOSubData(const void* data, unsigned int size,unsigned int offset) const noexcept
	{
		vb->UpdateSubData(data, size, offset);
	}

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;

private:
	unsigned int* vao;
	VertexBuffer* vb;
	IndexBuffer* ib;

	void SetupOpenGLBuffers();
};
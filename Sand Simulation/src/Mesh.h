#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <vector>

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

    void Clear() noexcept
    {
        indices.clear();
        vertices.clear();

		/*indices.erase(indices.begin(), indices.end());
		vertices.erase(vertices.begin(), vertices.end());

        glBindVertexArray(*vao);
        UploadIBOData();
        UploadVBOData();*/
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
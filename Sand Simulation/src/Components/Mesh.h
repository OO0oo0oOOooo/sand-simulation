#pragma once

#include "../Scene/GameObject.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/Vertex.h"
#include <vector>

const glm::vec3 vertexPositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
};

const unsigned int meshTriangles[] = {
    0, 1, 2,
    2, 1, 3,
};

//struct MeshData
//{
//    std::vector<Vertex> Vertices;
//    std::vector<unsigned int> Indices;
//
//    void Clear()
//	{
//        Vertices.clear();
//		Indices.clear();
//	}
//};

class Mesh : public Component
{
public:
    Mesh(GameObject* obj);

    void Clear();
    void ClearBuffers();

    void UploadData();
    void UploadSubData(int offsetV, int offsetI);

public:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    //TODO: Take in the vertex specific data and build the vertex here
    //std::vector<float> vertices;
    //std::vector<unsigned int> indices;
    //std::vector<float> normals;
    //std::vector<float> texCoords;
    //std::vector<glm::vec4> colors;

    //Todo: It might be worth it to store indices as triangles

    //Todo: Move this back into private and create a const refrence getter
    VertexArray m_VertexArray;
private:
};

/*
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void Bind();
    void Unbind();

    void Clear();
    void ClearBuffers();

    void UploadIBOData();
    void UploadVBOData();
    void UploadVBOSubData(const void* data, unsigned int size, unsigned int offset);


    std::vector<unsigned int> Indices;
    std::vector<Vertex> Vertices;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> tangents;
    std::vector<float> texCoords;
    std::vector<glm::vec4> colors;

private:
    void SetupOpenGLBuffers();

    unsigned int* vao;
    VertexBuffer* vb;
    IndexBuffer* ib;
};
*/

/*
class Mesh
{
public:
    Mesh();
    ~Mesh();

    void Draw() const noexcept
    {
        glBindVertexArray(*vao);
        MeshShader->Bind();
        ib->Bind();

        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    void DrawLine() const noexcept
    {
		glBindVertexArray(*vao);
        MeshShader->Bind();
		ib->Bind();

		glDrawElements(GL_LINES, Indices.size(), GL_UNSIGNED_INT, nullptr);
	}

    void Clear() noexcept
    {
        Indices.clear();
        Vertices.clear();
	}

    void ClearBuffers() noexcept
    {
        Indices.clear();
        Vertices.clear();

        ib->UpdateData(Indices);
        vb->UpdateData(Vertices);
	}

    void UploadIBOData() noexcept
	{
		ib->UpdateData(Indices);
	}

    void UploadVBOData() noexcept
    {
        vb->UpdateData(Vertices);
    }

    void UploadVBOSubData(const void* data, unsigned int size,unsigned int offset) const noexcept
	{
		vb->UpdateSubData(data, size, offset);
	}

    std::vector<unsigned int> Indices;
    std::vector<Vertex> Vertices;
    Shader* MeshShader;

private:
	unsigned int* vao;
	VertexBuffer* vb;
	IndexBuffer* ib;

	void SetupOpenGLBuffers();
};
*/
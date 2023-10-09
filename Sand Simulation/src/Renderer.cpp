#include "Renderer.h"

#include "MeshData.h"

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer()
{
    vao = new unsigned int;
    vb = new VertexBuffer(0, 0);
    ib = new IndexBuffer(0, 0);
    shader = new Shader();

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader->Bind();
    shader->SetUniformMat4f("u_ViewProjection", VP);
    shader->SetUniformMat4f("u_Transform", model);

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    glEnableVertexAttribArray(1);

    GenerateTerrainMap();
    UpdateBuffers();
}

Renderer::~Renderer()
{
    delete vao;
    delete vb;
    delete ib;
    delete shader;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw()
{
    glBindVertexArray(*vao);
    shader->Bind();
    ib->Bind();
    glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::GenerateTerrainMap()
{
    TerrainMap = std::vector<std::vector<TerrainData>>(tilesX, std::vector<TerrainData>(tilesY));

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            TerrainMap[x][y].type = 1;
        }
    }
}

void Renderer::UpdateBuffers()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (TerrainMap[x][y].type == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    vertices.push_back({ (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)tileSize, vertexColors[i] });
                }

                for (int i = 0; i < 6; i++)
                {
                    indices.push_back(meshTriangles[i] + (vertices.size() - 4));
                }
            }
        }
    }

    std::cout << "Vertices: " << vertices.size() << std::endl;
    std::cout << "Indices: " << indices.size() << std::endl;

    vb->UpdateData(vertices.data(), vertices.size() * sizeof(Vertex));
    ib->UpdateData(indices.data(), indices.size());
}
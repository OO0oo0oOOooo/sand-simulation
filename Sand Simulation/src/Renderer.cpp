#include "Renderer.h"
#include "ParticleData.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer()
{
}

Renderer::Renderer(int windowWidth, int windowHeight)
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
    shader->SetUniform4f("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    glEnableVertexAttribArray(1);
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

void Renderer::UpdateBuffers(Grid* grid)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < grid->GridWidth; x++)
    {
        for (int y = 0; y < grid->GridHeight; y++)
        {
            for (int i = 0; i < 4; i++)
            {
                vertices.push_back({ (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)grid->CellSize, grid->GetCell(x,y).color });
            }

            for (int i = 0; i < 6; i++)
            {
                indices.push_back(meshTriangles[i] + (vertices.size() - 4));
            }
        }
    }

    vb->UpdateData(vertices.data(), vertices.size() * sizeof(Vertex));
    ib->UpdateData(indices.data(), indices.size());
}

void Renderer::SetShaderUniforms(float width, float height)
{
    glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader->Bind();
    shader->SetUniformMat4f("u_ViewProjection", VP);
    shader->SetUniformMat4f("u_Transform", model);
    shader->SetUniform4f("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}
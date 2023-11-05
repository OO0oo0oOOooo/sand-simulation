#include "Renderer.h"
#include "Cell.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer(int windowWidth, int windowHeight)
{
    mesh = new Mesh();
    shader = new Shader();

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader->Bind();
    shader->SetUniformMat4f("u_ViewProjection", VP);
    shader->SetUniformMat4f("u_Transform", model);
    shader->SetUniform4f("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

Renderer::~Renderer()
{
    delete mesh;
    delete shader;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw()
{
    mesh->Draw(shader);
}

void Renderer::InitBuffers(Grid* grid)
{
    mesh->vertices.resize(grid->GridWidth * grid->GridHeight * 4);
    mesh->indices.resize(grid->GridWidth * grid->GridHeight * 6);

    for (int x = 0; x < grid->GridWidth; x++)
    {
        for (int y = 0; y < grid->GridHeight; y++)
        {
            int baseVertexIndex = (y * grid->GridWidth + x) * 4;
            int baseIndexIndex = (y * grid->GridWidth + x) * 6;

            for (int i = 0; i < 6; i++)
            {
                mesh->indices[baseIndexIndex + i] = meshTriangles[i] + baseVertexIndex;
            }
        }
    }

    mesh->UploadIBOData();
}

void Renderer::UpdateBuffers(Grid* grid)
{
    for (int x = 0; x < grid->GridWidth; x++)
    {
        for (int y = 0; y < grid->GridHeight; y++)
        {
            Cell& cell = grid->GetCellRefrence(x, y);
            if (cell.dirty)
            {
                int baseVertexIndex = (y * grid->GridWidth + x) * 4;

                for (int i = 0; i < 4; i++)
                {
                    mesh->vertices[baseVertexIndex + i].position = (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)grid->CellSize;
                    mesh->vertices[baseVertexIndex + i].color = cell.color;
                }

                cell.dirty = false;
            }
        }
    }

    mesh->UploadVBOData();
}

void Renderer::UpdateDirtyBuffers(Grid* grid)
{
    if (grid->DirtyCells.size() <= 0)
        return;

    for (int x = 0; x < grid->DirtyCells.size(); x++)
    {
        Vertex v[4];

        glm::ivec2 pos = grid->DirtyCells[x].position;
        Cell& cell = grid->GetCellRefrence(pos.x, pos.y);

        for (int i = 0; i < 4; i++)
        {
            v[i].position = (glm::vec3(pos.x, pos.y, 0) + vertexPositions[i]) * (float)grid->CellSize;
            v[i].color = cell.color;
        }

        int baseVertexIndex = (pos.y * grid->GridWidth + pos.x) * 4;

        mesh->UploadVBOSubData(v, 4 * sizeof(Vertex), baseVertexIndex * sizeof(Vertex));
    }

    grid->ClearDirtyCells();
}
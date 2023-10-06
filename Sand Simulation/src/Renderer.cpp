#include "Renderer.h"

#include "MeshData.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer()
{
    //GenerateTerrainMap();
    //UpdateBuffers();

    shader = Shader();
    shader.Bind();

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader.SetUniformMat4f("u_ViewProjection", VP);
    shader.SetUniformMat4f("u_Transform", model);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vb = VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
    ib = IndexBuffer(m_Indices.data(), m_Indices.size() * sizeof(unsigned int));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
    glEnableVertexAttribArray(1);
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw()
{
    shader.Bind();
    ib.Bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Renderer::AddVertex(Vertex vertex)
{
	m_Vertices.push_back(vertex);
}

void Renderer::AddIndex(unsigned int index)
{
	m_Indices.push_back(index);
}

void Renderer::UpdateBuffers()
{
	m_Vertices.clear();
	m_Indices.clear();

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (TerrainMap[x][y].type == 1)
            {
                for (int i = 0; i < 4; i++)
                {
					m_Vertices.push_back({ (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)tileSize, vertexColors[i] });
				}

                for (int i = 0; i < 6; i++)
                {
					m_Indices.push_back(meshTriangles[i] + (m_Vertices.size() - 4));
				}
			}
		}
	}
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

#include "Grid.h"
#include "MeshData.h"
#include <GL/glew.h>

Grid::Grid()
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

Grid::~Grid()
{
}

void Grid::UpdateArrays()
{

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
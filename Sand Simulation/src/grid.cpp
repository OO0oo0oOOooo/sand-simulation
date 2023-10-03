#include "grid.h"

Grid::Grid()
{
    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            TerrainMap[x][y].type = 0;
        }
    }
}

Grid::~Grid()
{
}

void Grid::Update()
{
    /*for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (TerrainMap[x][y].type == 1)
            {
                if (y < tilesY - 1)
                {
                    if (TerrainMap[x][y + 1].type == 0)
                    {
						TerrainMap[x][y + 1].type = 1;
						TerrainMap[x][y].type = 0;
					}
				}
			}
		}
	}*/

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
}   
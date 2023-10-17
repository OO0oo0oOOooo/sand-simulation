#include "Grid.h"

Grid::Grid()
{
	CellSize = 1;
	GridWidth = 1;
	GridHeight = 1;

	CellMap = std::vector<std::vector<Particle>>(GridWidth, std::vector<Particle>(GridHeight));
}

//Grid::Grid(int width, int height, int cellSize)
//{
//	CellSize = cellSize;
//	GridWidth = width;
//	GridHeight = height;
//
//	CellMap = std::vector<std::vector<Particle>>(GridWidth, std::vector<Particle>(GridHeight));
//}

Grid::Grid(int windowWidth, int windowHeight, int resolution)
{
	CellSize =   windowWidth  / resolution;
	GridWidth =	 windowWidth  / CellSize;
	GridHeight = windowHeight / CellSize;

	CellMap = std::vector<std::vector<Particle>>(GridWidth, std::vector<Particle>(GridHeight));
}

Grid::~Grid()
{
}

void Grid::InitGrid()
{
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			CellMap[x][y] = ParticleSand;
		}
	}
}

void Grid::UpdateGrid()
{
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			// Update Particles
		}
	}
}

void Grid::ClearGrid()
{
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			CellMap[x][y] = ParticleVoid;
		}
	}
}

//void Grid::DrawGrid(Renderer* renderer)
//{
//	renderer->UpdateBuffers();
//}

//Particle GetCell(int x, int y)
//{
//	if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
//		return ParticleAir;
//
//	return CellMap[x][y];
//}
//
//void Grid::SetCell(int x, int y, Particle particle)
//{
//	if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
//		return;
//
//	CellMap[x][y] = particle;
//}



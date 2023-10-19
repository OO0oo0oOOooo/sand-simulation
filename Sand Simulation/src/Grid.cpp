#include "Grid.h"

Grid::Grid()
{
	CellSize = 1;
	GridWidth = 1;
	GridHeight = 1;

	CellMap = std::vector<std::vector<Particle>>(GridWidth, std::vector<Particle>(GridHeight));
}

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
			CellMap[x][y] = ParticleAir;
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
			// UpdateSand(x, y);
			// UpdateWater(x, y);

			// Sand
			if (GetCell(x, y).type == ParticleSand.type)
			{
				if (GetCell(x, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x, y - 1, ParticleSand);
				}
				else if (GetCell(x + 1, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y - 1, ParticleSand);
				}
				else if (GetCell(x - 1, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y - 1, ParticleSand);
				}
			}

			// Water
			if (GetCell(x, y).type == ParticleWater.type)
			{
				if (GetCell(x, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x, y - 1, ParticleWater);
				}
				else if (GetCell(x + 1, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y - 1, ParticleWater);
				}
				else if (GetCell(x - 1, y - 1).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y - 1, ParticleWater);
				}
				else if (GetCell(x + 1, y).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y, ParticleWater);
				}
				else if (GetCell(x - 1, y).type == ParticleAir.type)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y, ParticleWater);
				}
			}
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
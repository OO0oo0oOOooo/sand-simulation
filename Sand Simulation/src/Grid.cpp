#include "Grid.h"

Grid::Grid(int windowWidth, int windowHeight, int resolution)
{
	CellSize =   windowWidth  / resolution;
	GridWidth =	 windowWidth  / CellSize;
	GridHeight = windowHeight / CellSize;

	CellMap = std::vector<Cell>(GridWidth * GridHeight);

	InitGrid();
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
			CellMap[x + y * GridWidth] = ParticleAir;
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
			if (GetCell(x, y).Id == ParticleSand.Id)
			{
				if (GetCell(x, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x, y - 1, ParticleSand);
				}
				else if (GetCell(x + 1, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y - 1, ParticleSand);
				}
				else if (GetCell(x - 1, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y - 1, ParticleSand);
				}
			}

			// Water
			if (GetCell(x, y).Id == ParticleWater.Id)
			{
				if (GetCell(x, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x, y - 1, ParticleWater);
				}
				else if (GetCell(x + 1, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y - 1, ParticleWater);
				}
				else if (GetCell(x - 1, y - 1).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y - 1, ParticleWater);
				}
				else if (GetCell(x + 1, y).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x + 1, y, ParticleWater);
				}
				else if (GetCell(x - 1, y).Id == ParticleAir.Id)
				{
					SetCell(x, y, ParticleAir);
					SetCell(x - 1, y, ParticleWater);
				}
			}

			// Render Changes

		}
	}
}

//char Grid::CheckCellBounds(int x, int y)
//{
//	// BitShift to reaction.
//	return 00000000;
//}

void Grid::ClearGrid()
{
	for (int x = 0; x < GridWidth; x++)
	{
		for (int y = 0; y < GridHeight; y++)
		{
			CellMap[GetIndexFromFlat2DArray(x, y)] = ParticleAir;
		}
	}
}
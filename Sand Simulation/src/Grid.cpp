#include "Grid.h"

Grid::Grid()
{
	CellSize = 1;
	GridWidth = 1;
	GridHeight = 1;

	//CellMap = std::vector<std::vector<Cell>>(GridWidth, std::vector<Cell>(GridHeight));
	CellMap = std::vector<Cell>(GridWidth * GridHeight);
}

Grid::Grid(int gridWidth, int gridHeight)
	: GridWidth(gridWidth), GridHeight(gridHeight)
{
	CellSize = 20;

	//CellMap = std::vector<std::vector<Cell>>(GridWidth, std::vector<Cell>(GridHeight));
	CellMap = std::vector<Cell>(GridWidth * GridHeight);
}

Grid::Grid(int windowWidth, int windowHeight, int resolution)
{
	CellSize =   windowWidth  / resolution;
	GridWidth =	 windowWidth  / CellSize;
	GridHeight = windowHeight / CellSize;

	//CellMap = std::vector<std::vector<Cell>>(GridWidth, std::vector<Cell>(GridHeight));
	CellMap = std::vector<Cell>(GridWidth * GridHeight);
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
			//CellMap[x][y] = ParticleAir;
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

			// Determine if cell can switch with colliding cell

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
			//CellMap[x][y] = ParticleVoid;
			CellMap[GetIndexFromFlat2DArray(x, y)] = ParticleVoid;
		}
	}
}
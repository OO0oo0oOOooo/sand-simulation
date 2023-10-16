#pragma once

#include <vector>

#include "ParticleData.h"
#include "Renderer.h"

class Grid
{
public:
	Grid();
	//Grid(int gridWidth, int gridHeight, int cellSize);
	Grid(int windowWidth, int windowHeight, int resolution);
	
	~Grid();

	void InitGrid();
	void UpdateGrid();
	void ClearGrid();

	// void DrawGrid(Renderer* renderer);

	inline Particle GetCell(int x, int y)
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return ParticleAir;
		
		return CellMap[x][y]; 
	}

	inline void SetCell(int x, int y, Particle particle) 
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return;

		CellMap[x][y] = particle;
	}

	inline int GetWidth() { return GridWidth; }
	inline int GetHeight() { return GridHeight; }
	inline int GetCellSize() { return CellSize; }

	inline void SetWidth(int gridWidth) { GridWidth = gridWidth; }
	inline void SetHeight(int gridHeight) { GridHeight = gridHeight; }
	inline void SetCellSize(int cellSize) { CellSize = cellSize; }

	// This could be used for saving and loading
	// inline std::vector<std::vector<Particle>> GetCellMap() { return CellMap; }
	// inline void SetCellMap(std::vector<std::vector<Particle>> cellMap) { CellMap = cellMap; }
	
	// inline int GetCellIndex(int x, int y, int Width) { return y * Width + x } // This is for a flattened array


private:
	int GridWidth;
	int GridHeight;
	int CellSize;

	std::vector<std::vector<Particle>> CellMap;

	//void DrawGridLines(Renderer* renderer);
	//void DrawParticles(Renderer* renderer);



};

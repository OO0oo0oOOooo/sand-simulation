#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "Cell.h"
#include "Window.h"

class Grid
{
public:
	Grid();
	Grid(int gridWidth, int gridHeight);
	Grid(int windowWidth, int windowHeight, int resolution);
	
	~Grid();

	void InitGrid();
	void UpdateGrid();
	void ClearGrid();

	inline Cell& GetCellRefrence(int x, int y)
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			throw std::out_of_range("Index out of bounds");

		return CellMap[GetIndexFromFlat2DArray(x, y)];
	}

	inline Cell GetCell(int x, int y)
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return ParticleVoid;

		return CellMap[GetIndexFromFlat2DArray(x, y)];
	}

	inline void SetCell(int x, int y, Cell particle)
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return;

		CellMap[GetIndexFromFlat2DArray(x, y)] = particle;
		CellMap[GetIndexFromFlat2DArray(x, y)].dirty;
	}

	inline glm::ivec2 GetCellIndex(glm::vec2 normalizedPos)
	{
		int x = (int)(normalizedPos.x * GridWidth);
		int y = (int)(normalizedPos.y * GridHeight);

		return glm::ivec2(x, y);
	}

	inline int GetIndexFromFlat2DArray(int x, int y)
	{
		return (y * GridWidth + x);
	}

	// This could be used for saving and loading
	// inline std::vector<std::vector<Particle>> GetCellMap() { return CellMap; }
	// inline void SetCellMap(std::vector<std::vector<Particle>> cellMap) { CellMap = cellMap; }

	//char CheckCellBounds(int x, int y);
	
	int GridWidth;
	int GridHeight;
	int CellSize;

	std::vector<Cell> DirtyCells;
private:
	std::vector<Cell> CellMap;

	//std::vector<std::vector<Cell>> CellMap;

	//void DrawGridLines(Renderer* renderer);
	//void DrawParticles(Renderer* renderer);
};

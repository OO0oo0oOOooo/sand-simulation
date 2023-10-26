#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "ParticleData.h"
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

	inline Particle GetCell(int x, int y)
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return ParticleVoid;
		
		return CellMap[x][y];
	}

	inline void SetCell(int x, int y, Particle particle) 
	{
		if (x < 0 || x >= GridWidth || y < 0 || y >= GridHeight)
			return;

		CellMap[x][y] = particle;
	}

	inline glm::ivec2 GetCellIndex(glm::vec2 normalizedPos)
	{
		int x = (int)(normalizedPos.x * GridWidth);
		int y = (int)(normalizedPos.y * GridHeight);

		return glm::ivec2(x, y);
	}

	// This could be used for saving and loading
	// inline std::vector<std::vector<Particle>> GetCellMap() { return CellMap; }
	// inline void SetCellMap(std::vector<std::vector<Particle>> cellMap) { CellMap = cellMap; }
	
	int GridWidth;
	int GridHeight;
	int CellSize;

private:
	std::vector<std::vector<Particle>> CellMap;

	//void DrawGridLines(Renderer* renderer);
	//void DrawParticles(Renderer* renderer);
};

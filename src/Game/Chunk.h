#pragma once

#include "Cells/Cell.h"
#include <vector>

class Chunk
{
public:
	Chunk(int width, int height, int scale, int x, int y);

	void Start();
	void Update();

	Chunk* GetChunk(int x, int y);

	Cell GetCell(int index);
	Cell GetCell(int x, int y);

	void SetCell(int index, Cell cell);
	void SetCell(int x, int y, Cell cell);

	void MoveCell(int x, int y, int tX, int tY );
	
	void TempSetSand(int x, int y);

public:
	// Todo: Get and Set all these from world when chunk is constructed
	const int m_Width = 64;
	const int m_Height = 64;
	const int m_Scale = 5;
	const int m_X = 0;
	const int m_Y = 0;

	Chunk* m_Neighbor[9];
	
	std::vector <std::tuple<Chunk*, unsigned int, unsigned int>> m_MoveList;

	unsigned char* textureData = new unsigned char[m_Width * m_Height * 4]; // cells * rgba

private:
	int GetIndex(int x, int y)
	{
		int nx = ((x % 64) + 64) % 64;
		int ny = ((y % 64) + 64) % 64;
		return ny * m_Width + nx;
	}

	bool IsOutOfBounds(int x, int y) { return x < 0 || x >= m_Width || y < 0 || y >= m_Height; }

	bool IsEmpty(int index) { if (m_Cells[index].id == 0) return true; else return false; }
	bool IsEmpty(int x, int y) { if (GetCell(x, y).id == 0) return true; else return false; }

	bool UpdateState();
	//void SetCellColor(int x, int y, glm::u8vec4 color);

	void Commit();

	bool MoveDown(int x, int y, Cell cell);
	bool MoveSide(int x, int y, Cell cell);
	bool MoveDownSide(int x, int y, Cell cell);

private:

	Cell m_Cells[4096];
	
	// Image buffer

	bool m_ShouldUpdate = false;
	bool m_ShouldUpdateNextFrame = false;
};
#include "Chunk.h"
#include <algorithm>

Chunk::Chunk(int width, int height, int scale, int x, int y) : m_Width(width), m_Height(height), m_Scale(scale), m_X(x), m_Y(y)
{
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			int index = GetIndex(x, y) * 4;

			m_Cells[GetIndex(x, y)] = { 0, { x, y }, { 0, 0 }, { 0, 0, 0, 0 } };
			textureData[index + 0] = 0;
			textureData[index + 1] = 0;
			textureData[index + 2] = 0;
			textureData[index + 3] = 0;
		}
	}
}

void Chunk::Start() {}

void Chunk::Update()
{
	if (!UpdateState() && m_MoveList.size() == 0)
		return;

	for (int x = 0; x < m_Width; x++)
	{
		for (int y = 0; y < m_Height; y++)
		{
			Cell cell = GetCell(x, y);

			if (cell.id == 3 && MoveDown(x, y, cell)) {}
			else if (cell.id == 3 && MoveDownSide(x, y, cell)) {}
			else if (cell.id == 3 && MoveSide(x, y, cell)) {}
		}
	}

	Commit();
}

bool Chunk::MoveDown(int x, int y, Cell cell)
{
	bool down = IsEmpty(x, y - 1);
	if (down)
	{
		MoveCell(x, y, x, y - 1);
	}

	return down;
}

bool Chunk::MoveSide(int x, int y, Cell cell)
{
	bool left  = IsEmpty(x - 1, y);
	bool right = IsEmpty(x + 1, y);

	if (left && right)
	{
		left = std::rand() % 2;
		right = !left;
	}

	if (left) MoveCell(x, y, x - 1, y);
	else if (right) MoveCell(x, y, x + 1, y);

	return left || right;
}

bool Chunk::MoveDownSide(int x, int y, Cell cell)
{
	bool downLeft  = IsEmpty(x - 1, y - 1);
	bool downRight = IsEmpty(x + 1, y - 1);

	if (downLeft && downRight)
	{
		downLeft = std::rand() % 2;
		downRight = !downLeft;
	}

	if (downLeft) MoveCell(x, y, x - 1, y - 1);
	else if (downRight) MoveCell(x, y, x + 1, y - 1);

	return downLeft || downRight;
}

void Chunk::MoveCell(int x, int y, int tX, int tY)
{
	Chunk* startChunk  = GetChunk(x, y);
	Chunk* targetChunk = GetChunk(tX, tY);

	if (!startChunk)  { return; }
	if (!targetChunk) { return; }

	targetChunk->m_MoveList.emplace_back(startChunk, GetIndex(x, y), GetIndex(tX, tY));
}

Chunk* Chunk::GetChunk(int x, int y)
{
	if (IsOutOfBounds(x, y))
	{
		int cx = 1;
		int cy = 1;
		int adjustedX = x;
		int adjustedY = y;

		if (x < 0)
		{
			adjustedX += 64;
			cx -= 1;
		}
		else if (x > 63)
		{
			adjustedX -= 64;
			cx += 1;
		}

		if (y < 0)
		{
			adjustedY += 64;
			cy -= 1;
		}
		else if (y > 63)
		{
			adjustedY -= 64;
			cy -= 1;
		}

		int index = cy * 3 + cx;
		
		if(m_Neighbor[index] != nullptr)
			return m_Neighbor[index]->GetChunk(adjustedX, adjustedY);

		return nullptr;
	}

	return this;
}

Cell Chunk::GetCell(int x, int y)
{
	if (IsOutOfBounds(x, y))
	{
		int cx = 1;
		int cy = 1;
		int adjustedX = x;
		int adjustedY = y;

		if (x < 0)
		{
			adjustedX += 64;
			cx -= 1;
		}
		else if (x > 63)
		{
			adjustedX -= 64;
			cx += 1;
		}

		if (y < 0)
		{
			adjustedY += 64;
			cy -= 1;
		}
		else if (y > 63)
		{
			adjustedY -= 64;
			cy -= 1;
		}

		int index = cy * 3 + cx;

		if(m_Neighbor[index] != nullptr)
			return m_Neighbor[index]->GetCell(adjustedX, adjustedY);

		return Cell{ 255, { 0, 0 }, { 0, 0 }, { 0, 0, 0, 0 } };
	}

	return m_Cells[GetIndex(x, y)];
}

Cell Chunk::GetCell(int index)
{
	return m_Cells[index];
}

void Chunk::SetCell(int x, int y, Cell cell)
{
	if (IsOutOfBounds(x, y))
	{
		int cx = 1;
		int cy = 1;
		int adjustedX = x;
		int adjustedY = y;

		if (x < 0)
		{
			adjustedX += 64;
			cx -= 1;
		}
		else if (x > 63)
		{
			adjustedX -= 64;
			cx += 1;
		}

		if (y < 0)
		{
			adjustedY += 64;
			cy -= 1;
		}
		else if (y > 63)
		{
			adjustedY -= 64;
			cy -= 1;
		}

		int index = cy * 3 + cx;

		if (m_Neighbor[index] != nullptr)
			m_Neighbor[index]->SetCell(adjustedX, adjustedY, cell);

		return;
	}

	int index = GetIndex(x, y);
	SetCell(index, cell);
}

void Chunk::SetCell(int index, Cell cell)
{
	m_Cells[index].id = cell.id;
	//m_CellMap[GetIndex(x, y)].position = cell.position;
	m_Cells[index].velocity = cell.velocity;
	m_Cells[index].color = cell.color;

	int textureIndex = index * 4;
	textureData[textureIndex + 0] = cell.color.r;
	textureData[textureIndex + 1] = cell.color.g;
	textureData[textureIndex + 2] = cell.color.b;
	textureData[textureIndex + 3] = cell.color.a;

	// TODO: If on the boarder then update neighbours as well
	m_ShouldUpdateNextFrame = true;
}

void Chunk::Commit()
{
	for (size_t i = 0; i < m_MoveList.size(); i++)
	{
		if (m_Cells[std::get<2>(m_MoveList[i])].id != 0)
		{
			m_MoveList[i] = m_MoveList.back();
			m_MoveList.pop_back();
			i--;
		}
	}

	std::sort(m_MoveList.begin(), m_MoveList.end(), [](auto& a, auto& b) { return std::get<2>(a) < std::get<2>(b); } );
	
	size_t iprev = 0;
	m_MoveList.emplace_back(nullptr, -1, -1);
	for (size_t i = 0; i < m_MoveList.size() - 1; i++) {
		if (std::get<2>(m_MoveList[i + 1]) != std::get<2>(m_MoveList[i])) {
			size_t rand = iprev;
			if (i > iprev)
			{
				rand = iprev + std::rand() % (i - iprev);
			}

			unsigned int src = std::get<1>(m_MoveList[rand]);
			unsigned int dst = std::get<2>(m_MoveList[rand]);
			Chunk* chunk = std::get<0>(m_MoveList[rand]);

			SetCell(dst, chunk->GetCell(src));
			chunk->SetCell(src, { 0, { 0, 0 }, { 0, 0 }, { 0, 0, 0, 0 } });

			iprev = i + 1;
		}
	}

	m_MoveList.clear();
}




void Chunk::TempSetSand(int x, int y)
{
	Cell cell{ 3, { x, y }, {0, 0}, { 230, 178, 51, 255 } };
	SetCell(x, y, cell);
}

bool Chunk::UpdateState()
{
	m_ShouldUpdate = m_ShouldUpdateNextFrame;
	m_ShouldUpdateNextFrame = false;

	return m_ShouldUpdate;
}

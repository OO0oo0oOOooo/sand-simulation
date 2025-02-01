#include "Chunk.h"
#include <algorithm>

Chunk::Chunk(int width, int height, int scale, int x, int y) : m_Width(width), m_Height(height), m_Scale(scale), m_X(x), m_Y(y)
{
	if (m_Mesh == nullptr)
		return;

	// Init cells with "Air"
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			m_Cells[GetIndex(x, y)] = { 0, { x, y }, { 0, 0 }, { 0, 0, 0, 0 } };
		}
	}

	// Build mesh
	m_Mesh->Clear();
	m_Mesh->Vertices.resize(4096 * 4);
	m_Mesh->Indices.resize(4096 * 6);

	for (int x = 0; x < m_Width; x++)
	{
		for (int y = 0; y < m_Height; y++)
		{
			int cellIndex = GetIndex(x, y);
			int baseVertexIndex = (cellIndex) * 4;
			int baseIndexIndex = (cellIndex) * 6;
			Cell cell = m_Cells[cellIndex];

			for (int i = 0; i < 4; i++)
			{
				m_Mesh->Vertices[baseVertexIndex + i].position = (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)m_Scale;
				m_Mesh->Vertices[baseVertexIndex + i].color = glm::vec4{ cell.color.x / 255.0f, cell.color.y / 255.0f, cell.color.z / 255.0f, cell.color.w / 255.0f };
			}

			for (int i = 0; i < 6; i++)
			{
				m_Mesh->Indices[baseIndexIndex + i] = meshTriangles[i] + baseVertexIndex;
			}
		}
	}

	m_Mesh->UploadData();
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

	m_Mesh->UploadData();
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

	m_Cells[GetIndex(x, y)].id = cell.id;
	//m_CellMap[GetIndex(x, y)].position = cell.position;
	m_Cells[GetIndex(x, y)].velocity = cell.velocity;
	m_Cells[GetIndex(x, y)].color = cell.color;

	SetCellColor(x, y, cell.color);

	//Todo: If on the boarder then update neighbours as well
	m_ShouldUpdateNextFrame = true;
}

void Chunk::SetCell(int index, Cell cell)
{
	m_Cells[index].id = cell.id;
	//m_CellMap[GetIndex(x, y)].position = cell.position;
	m_Cells[index].velocity = cell.velocity;
	m_Cells[index].color = cell.color;

	glm::vec2 pos = m_Cells[index].position;
	SetCellColor(pos.x, pos.y, cell.color);

	//Todo: If on the boarder then update neighbours as well
	m_ShouldUpdateNextFrame = true;
}

void Chunk::Commit()
{
	// Remove moves with destination occupied
	for (size_t i = 0; i < m_MoveList.size(); i++)
	{
		if (m_Cells[std::get<2>(m_MoveList[i])].id != 0)
		{
			m_MoveList[i] = m_MoveList.back();
			m_MoveList.pop_back();
			i--;
		}
	}

	// sort from lowest index to highest
	std::sort(m_MoveList.begin(), m_MoveList.end(), [](auto& a, auto& b) { return std::get<2>(a) < std::get<2>(b); } );
	
	// pick random
	size_t iprev = 0;
	m_MoveList.emplace_back(nullptr, -1, -1); // to catch final move

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

void Chunk::SetCellColor(int x, int y, glm::u8vec4 color)
{
	int baseVertexIndex = GetIndex(x, y) * 4;

	for (int i = 0; i < 4; i++)
	{
		m_Mesh->Vertices[baseVertexIndex + i].color = glm::vec4{ color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f };
	}
}



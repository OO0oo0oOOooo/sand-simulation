#include "World.h"
#include "../Events/EventManager.h" // TODO: Refactor this out

glm::ivec2 neighborPositions[9] =
{
	glm::ivec2(-1, -1),
	glm::ivec2(0, -1),
	glm::ivec2(1, -1),

	glm::ivec2(-1, 0),
	glm::ivec2(0, 0),
	glm::ivec2(1, 0),

	glm::ivec2(-1, 1),
	glm::ivec2(0, 1),
	glm::ivec2(1, 1),
};

World::World(GameObject* obj) : Component(obj)
{
	EventManager::GetInstance().MouseButtonDownEvent += std::bind(&World::MouseDown, this, std::placeholders::_1);
	EventManager::GetInstance().MouseButtonUpEvent += std::bind(&World::MouseUp, this, std::placeholders::_1);
	EventManager::GetInstance().MouseMoveEvent += std::bind(&World::MouseMoved, this, std::placeholders::_1, std::placeholders::_2);

	m_Chunks.reserve(m_WorldWidth * m_WorldHeight);

	m_Mesh = gameObject->GetComponent<Mesh>();
	m_Material = gameObject->GetComponent<Material>();

	m_Mesh->Vertices.resize(4);
	m_Mesh->Indices.resize(6);

	m_Mesh->Vertices[0].position = glm::vec3( 0.0f, 0.0f, 0.0f ) * (float)m_Scale;
	m_Mesh->Vertices[1].position = glm::vec3( 0.0f, 64.0f * 4.0f, 0.0f ) * (float)m_Scale;
	m_Mesh->Vertices[2].position = glm::vec3( 64.0f * 6.0f, 0.0f, 0.0f ) * (float)m_Scale;
	m_Mesh->Vertices[3].position = glm::vec3( 64.0f * 6.0f, 64.0f * 4.0f, 0.0f ) * (float)m_Scale;

	m_Mesh->Vertices[0].color	 = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	m_Mesh->Vertices[1].color	 = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
	m_Mesh->Vertices[2].color	 = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
	m_Mesh->Vertices[3].color	 = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );

	m_Mesh->Vertices[0].texCoord = glm::vec2( 0.0f, 0.0f );
	m_Mesh->Vertices[1].texCoord = glm::vec2( 0.0f, 1.0f );
	m_Mesh->Vertices[2].texCoord = glm::vec2( 1.0f, 0.0f );
	m_Mesh->Vertices[3].texCoord = glm::vec2( 1.0f, 1.0f );

	m_Mesh->Indices[0] = 0;
	m_Mesh->Indices[1] = 1;
	m_Mesh->Indices[2] = 2;
	m_Mesh->Indices[3] = 2;
	m_Mesh->Indices[4] = 1;
	m_Mesh->Indices[5] = 3;

	m_Mesh->UploadData();

	for (int y = 0; y < m_WorldHeight; y++)
	{
		for (int x = 0; x < m_WorldWidth; x++)
		{
			Chunk* chunkComponent = new Chunk(m_ChunkWidth, m_ChunkHeight, m_Scale, x, y);
			m_Chunks.emplace_back(chunkComponent);
		}
	}

	// provides chunks with their neighbours so they can interact
	for (int x = 0; x < m_WorldWidth; x++)
	{
		for (int y = 0; y < m_WorldHeight; y++)
		{
			for (int i = 0; i <= 8; i++)
			{
				int nx = x + neighborPositions[i].x;
				int ny = y + neighborPositions[i].y;

				if (nx < 0 || ny < 0 || nx >= m_WorldWidth || ny >= m_WorldHeight)
				{
					m_Chunks[GetIndex(x, y)]->m_Neighbor[i] = nullptr;
					continue;
				}

				m_Chunks[GetIndex(x, y)]->m_Neighbor[i] = m_Chunks[ny * m_WorldWidth + nx];
			}
		}
	}
}

void World::Update()
{
	if (m_CanPaint)
		EditElementAtPixel(m_X, m_Y);

	for (Chunk* chunk : m_Chunks)
	{
		chunk->Update();

		int xOffset = chunk->m_X * 64;
		int yOffset = chunk->m_Y * 64;

		m_Material->GetTexture()->UpdateSubData(chunk->textureData, 64, 64, xOffset, yOffset);
	}
}

void World::EditElementAtPixel(int x, int y)
{
	// TODO: should get pixel width and height from window
	if (x < 0 || x > 1919 || y < 0 || y > 1079)
		return;

	// Get world pos from pixel pos
	int wX = x / m_Scale;
	int wY = y / m_Scale;

	// Get chunk from world pos
	int cX = wX / m_ChunkWidth;
	int cY = wY / m_ChunkHeight;

	// Get local position
	int lX = wX - (cX * m_ChunkWidth);
	int lY = wY - (cY * m_ChunkHeight);

	m_Chunks[GetIndex(cX, cY)]->TempSetSand(lX, lY);
}

void World::MouseDown(int button)
{
	if (button == 0)
		m_CanPaint = true;
}

void World::MouseUp(int button)
{
	if (button == 0)
		m_CanPaint = false;
}

void World::MouseMoved(double x, double y)
{
	m_X = (int)x;
	m_Y = (int)y;
}

Cell World::GetCell(glm::ivec2 worldPos)
{
	int wX = worldPos.x;
	int wY = worldPos.y;

	int cX = wX / m_ChunkWidth;
	int cY = wY / m_ChunkHeight;

	int lX = wX - (cX * m_ChunkWidth);
	int lY = wY - (cY * m_ChunkHeight);

	return m_Chunks[GetIndex(cX, cY)]->GetCell(lX, lY);
}

void World::SetCell(glm::ivec2 worldPos, Cell cell)
{
	int wX = worldPos.x;
	int wY = worldPos.y;

	int cX = wX / m_ChunkWidth;
	int cY = wY / m_ChunkHeight;

	int lX = wX - (cX * m_ChunkWidth);
	int lY = wY - (cY * m_ChunkHeight);

	m_Chunks[GetIndex(cX, cY)]->SetCell(lX, lY, cell);
}

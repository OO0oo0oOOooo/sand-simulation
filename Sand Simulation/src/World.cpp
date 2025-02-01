#include "World.h"
#include "Events/EventManager.h"

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
	
	for (int y = 0; y < m_WorldHeight; y++)
	{
		for (int x = 0; x < m_WorldWidth; x++)
		{
			GameObject* gameObject = new GameObject(); // left off here
			gameObject->transform.SetPosition({ (x * m_ChunkWidth) * m_Scale, (y * m_ChunkHeight) * m_Scale, 0 });

			Mesh* meshComponent = new Mesh(gameObject);
			gameObject->AddComponent(meshComponent);

			Material* materialComponent = new Material(gameObject);
			gameObject->AddComponent(materialComponent);

			Chunk* chunkComponent = new Chunk(gameObject, m_ChunkWidth, m_ChunkHeight, m_Scale, x, y);
			gameObject->AddComponent(chunkComponent);

			m_Chunks.emplace_back(chunkComponent);

			//TODO: GameObjects should add themselves to the scene
			EventManager::GetInstance().AddGameObjectToScene(gameObject);
		}
	}

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
}

void World::EditElementAtPixel(int x, int y)
{
	// TODO should get pixel width and height from window
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
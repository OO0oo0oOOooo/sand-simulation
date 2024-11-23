#include "World.h"
#include "Events/EventManager.h"

const glm::ivec2 neighbourLUT[] = 
{
	glm::ivec2(-1, -1),
	glm::ivec2( 0, -1),
	glm::ivec2( 1, -1),
	glm::ivec2(-1,  0),
	glm::ivec2( 0,  0),
	glm::ivec2( 1,  0),
	glm::ivec2(-1,  1),
	glm::ivec2( 0,  1),
	glm::ivec2( 1,  1),
};

World::World(GameObject* obj) : Component(obj)
{
	//EventManager::GetInstance().EditElementAtWorldPosition += std::bind(&World::EditElementAtWorldPosition, this, std::placeholders::_1, std::placeholders::_2);
	EventManager::GetInstance().MouseButtonDownEvent += std::bind(&World::MouseDown, this, std::placeholders::_1);
	EventManager::GetInstance().MouseButtonUpEvent += std::bind(&World::MouseUp, this, std::placeholders::_1);
	EventManager::GetInstance().MouseMoveEvent += std::bind(&World::MouseMoved, this, std::placeholders::_1, std::placeholders::_2);

	m_Chunks.reserve(WORLD_WIDTH * WORLD_HEIGHT);
	
	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < WORLD_WIDTH; x++)
		{
			GameObject* gameObject = new GameObject();
			gameObject->transform.SetPosition({ (x * 64) * CELL_SIZE_IN_PIXELS, (y * 64) * CELL_SIZE_IN_PIXELS, 0 });

			Mesh* meshComponent = new Mesh(gameObject);
			gameObject->AddComponent(meshComponent);

			Material* materialComponent = new Material(gameObject);
			gameObject->AddComponent(materialComponent);

			Chunk* chunkComponent = new Chunk(gameObject);
			gameObject->AddComponent(chunkComponent);

			m_Chunks.emplace_back(chunkComponent);

			//TODO: GameObjects should add themselves to the scene
			EventManager::GetInstance().AddGameObjectToScene(gameObject);
		}
	}

	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < WORLD_WIDTH; x++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (!IsOutOfBounds(x + neighbourLUT[i].x, y + neighbourLUT[i].y))
				{
					m_Chunks[GetIndex(x, y)]->Neighbours[i] = m_Chunks[GetIndex(x + neighbourLUT[i].x, y + neighbourLUT[i].y)];
				}
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
	int wX = x / CELL_SIZE_IN_PIXELS;
	int wY = y / CELL_SIZE_IN_PIXELS;

	// Get chunk from world pos
	int cX = wX / CHUNK_WIDTH;
	int cY = wY / CHUNK_HEIGHT;

	// Get local position
	int lX = wX - (cX * CHUNK_WIDTH);
	int lY = wY - (cY * CHUNK_HEIGHT);

	m_Chunks[GetIndex(cX, cY)]->TempSetSand(lX, lY);
}

void World::MouseDown(int button)
{
	if(button == 0)
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
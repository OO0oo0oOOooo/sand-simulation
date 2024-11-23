#include "Chunk.h"

#include "Elements/Empty.h"
#include "Elements/Air.h"
#include "Elements/Sand.h"

Chunk::Chunk(GameObject* obj) : Component(obj)
{
	m_Mesh = gameObject->GetComponent<Mesh>();
	if (m_Mesh == nullptr)
		return;

	// Set elements
	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int x = 0; x < CHUNK_WIDTH; x++)
		{
			m_Element[GetIndex(x, y)] = new Air(x, y);
		}
	}

	// Build mesh
	m_Mesh->Clear();
	m_Mesh->Vertices.resize(CHUNK_SIZE * 4);
	m_Mesh->Indices.resize(CHUNK_SIZE * 6);

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			int cellIndex = GetIndex(x, y);
			int baseVertexIndex = (cellIndex) * 4;
			int baseIndexIndex = (cellIndex) * 6;
			Element element = *m_Element[cellIndex];

			for (int i = 0; i < 4; i++)
			{
				m_Mesh->Vertices[baseVertexIndex + i].position = (glm::vec3(x, y, 0) + vertexPositions[i]) * (float)CELL_SIZE_IN_PIXELS;
				m_Mesh->Vertices[baseVertexIndex + i].color = glm::vec4{ element.Color.x / 255.0f, element.Color.y / 255.0f, element.Color.z / 255.0f, element.Color.w / 255.0f };
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
	if (!UpdateState())
		return;

	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int x = 0; x < CHUNK_WIDTH; x++)
		{
			m_Element[GetIndex(x, y)]->Step(this);
		}
	}

	m_Mesh->UploadData();
}

Element* Chunk::GetElement(int x, int y)
{
	if (IsOutOfBounds(x, y))
		return nullptr; //Todo: Get from neighbour

	return m_Element[GetIndex(x, y)];
}

void Chunk::SetElement(int x, int y, Element* element)
{
	if (IsOutOfBounds(x, y))
		return; //Todo: Tell Neighbour

	//Todo: If on the boarder then update neighbours as well
	m_ShouldUpdateNextFrame = true;

	element->Position = { x, y };

	delete m_Element[GetIndex(x, y)];
	m_Element[GetIndex(x, y)] = element;

	UpdateColor(x, y, element->Color);
}

void Chunk::SwapElements(Element* a, Element* b)
{
	if (a == nullptr || b == nullptr)
		assert(false);

	m_ShouldUpdateNextFrame = true;

	glm::i8vec2 PositionA = a->Position;
	glm::i8vec2 PositionB = b->Position;

	a->Position = PositionB;
	b->Position = PositionA;

	m_Element[GetIndex(PositionA.x, PositionA.y)] = b;
	m_Element[GetIndex(PositionB.x, PositionB.y)] = a;

	UpdateColor(PositionA.x, PositionA.y, a->Color);
	UpdateColor(PositionB.x, PositionB.y, b->Color);
}

void Chunk::TempSetSand(int x, int y)
{
	SetElement(x, y, new Sand(x, y));
}

bool Chunk::UpdateState()
{
	m_ShouldUpdate = m_ShouldUpdateNextFrame;
	m_ShouldUpdateNextFrame = false;

	return m_ShouldUpdate;
}

void Chunk::UpdateColor(int x, int y, glm::u8vec4 color)
{
	int baseVertexIndex = GetIndex(x, y) * 4;

	for (int i = 0; i < 4; i++)
	{
		m_Mesh->Vertices[baseVertexIndex + i].color = glm::vec4{ color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f };
	}
}
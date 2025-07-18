#pragma once

#include "../Core/GameObject.h"
#include "../Core/Components/Mesh.h"
#include "../Core/Components/Material.h"

#include "Chunk.h"
#include <vector>
#include <memory>

#include <functional> // Todo: remove after brush moved out

class World : public Component
{
public:
	World(GameObject* obj);

	void Update();

	void EditElementAtPixel(int x, int y);

	void MouseDown(int button);
	void MouseUp(int button);
	void MouseMoved(double x, double y);

	Cell GetCell(glm::ivec2 worldPos);
	void SetCell(glm::ivec2 worldPos, Cell cell);

private:
	int GetIndex(int x, int y) { return y * m_WorldWidth + x; }
	int GetIndex(glm::vec2 pos) { return pos.y * m_WorldWidth + pos.x; }
	bool IsOutOfBounds(int x, int y) { return x < 0 || x >= m_WorldWidth || y < 0 || y >= m_WorldHeight; }

private:
	const int m_WorldWidth = 6;
	const int m_WorldHeight = 4;
	const int m_ChunkWidth = 64;
	const int m_ChunkHeight = 64;
	int m_Scale = 5;

	std::vector<Chunk*> m_Chunks;

	std::shared_ptr<Mesh> m_Mesh;
	std::shared_ptr<Material> m_Material;

	// TODO: remove all below
	int m_X = 0; // Mouse X, Y
	int m_Y = 0;
	bool m_CanPaint = false;
};
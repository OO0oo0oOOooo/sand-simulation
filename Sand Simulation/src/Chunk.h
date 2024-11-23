#pragma once

//#include "Components/Component.h"

#include "GameObject.h"
#include "Components/Mesh.h"
#include "Components/Material.h"

#include "ChunkData.h"

#include "Elements/Element.h"

class Chunk : public Component
{
public:
	Chunk(GameObject* obj);

	void Start();
	void Update();

	Element* GetElement(int x, int y);
	void SetElement(int x, int y, Element* element);
	void SwapElements(Element* a, Element* b);


	void TempSetSand(int x, int y);

public:
	Chunk* Neighbours[8] = { nullptr };

private:
	int GetIndex(int x, int y) { return y * CHUNK_WIDTH + x; }
	bool IsOutOfBounds(int x, int y) { return x < 0 || x >= CHUNK_WIDTH || y < 0 || y >= CHUNK_HEIGHT; }

	bool UpdateState();

	void UpdateColor(int x, int y, glm::u8vec4 color);

private:
	Element* m_Element[CHUNK_SIZE] = { nullptr };
	Mesh* m_Mesh;

	bool m_ShouldUpdate = false;
	bool m_ShouldUpdateNextFrame = false;
};
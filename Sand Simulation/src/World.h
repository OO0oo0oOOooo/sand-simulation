#pragma once

#include "Chunk.h"
#include <vector>

class World : public Component
{
public:
	World(GameObject* obj);

	void Update();

	void EditElementAtPixel(int x, int y);

	void MouseDown(int button);
	void MouseUp(int button);
	void MouseMoved(double x, double y);

private:
	int GetIndex(int x, int y) { return y * WORLD_WIDTH + x; }
	bool IsOutOfBounds(int x, int y) { return x < 0 || x >= WORLD_WIDTH || y < 0 || y >= WORLD_HEIGHT; }

private:
	std::vector<Chunk*> m_Chunks;

	// TODO: refactor this out when it becomes nessisary
	bool m_CanPaint = false;
	int m_X = 0;
	int m_Y = 0;
};
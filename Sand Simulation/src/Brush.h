
/*
#pragma once

#include "World.h"
#include "Window.h"

enum BrushType
{
	Sphere,
	Rectangle,
};

class Brush
{
public:
	Brush(World* world);

	void UpdateMousePosition(int x, int y);
	void BeginPaint(int key);
	void EndPaint(int key);
	void Paint();

	//void SelectElement(Window window);
	//void ChangeBrush();
	//void ChangeBrushSize();

private:
	int m_Selected = 3;
	int m_BrushSize = 1;
	int m_BrushType = 0;
	glm::vec2 m_MousePosition;

	bool m_Draw = false;
	bool m_Erase = false;

	World* m_World;
};
*/
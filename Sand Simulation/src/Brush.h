#pragma once

#include "World.h"
#include "Input.h"
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

	void BeginPaint(int key, glm::vec2 position);
	void EndPaint(int key, glm::vec2 position);
	void Paint();

	//void SelectElement(Window window);
	//void ChangeBrush();
	//void ChangeBrushSize();

private:
	int m_Selected = 3;
	int m_BrushSize = 1;
	int m_BrushType = 0;

	bool m_Draw = false;
	bool m_Erase = false;

	World* m_World;
};
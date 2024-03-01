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
	Brush()
	{
		_selected = 3;
		_brushSize = 1;
	}

	~Brush(){}

	void MouseInput(Window window, World* world);
	void SelectionInput(Window window);

private:
	int _selected;
	int _brushSize;
};
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
		_brushType = 0;
	}

	~Brush(){}

	void Paint(Window window, World* world);
	void SelectElement(Window window);

	void ChangeBrush();
	void ChangeBrushSize();

private:
	int _selected;
	int _brushSize;
	int _brushType;
};
#pragma once

#include "QuadTreeObject.h"
#include "Cell.h"
#include "Window.h"
#include "Grid.h"
#include "Input.h"

namespace Brush
{
	extern Cell selectedParticle;
	extern int brushSize;

	void MouseInput(Window window, Grid* grid, QuadTreeObject* quadTreeObject);
	void SelectionInput(Window window, Grid* grid);
}
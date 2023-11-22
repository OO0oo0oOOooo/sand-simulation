#pragma once

#include "World.h"
#include "Input.h"
#include "Window.h"
#include "Cell.h"

namespace Brush
{
	extern Cell selectedParticle;
	extern int brushSize;

	void MouseInput(Window window, World* world);
	void SelectionInput(Window window);
}
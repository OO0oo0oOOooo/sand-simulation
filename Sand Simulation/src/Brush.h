#pragma once

#include "ParticleData.h"
#include "Window.h"
#include "Grid.h"
#include "Input.h"

namespace Brush
{
	extern ParticleSelection selectedParticle;
	extern int brushSize;

	Particle GetSelectedParticle(ParticleSelection selection);
	void MouseInput(Window window, Grid* grid);
	void SelectionInput(Window window, Grid* grid);
}
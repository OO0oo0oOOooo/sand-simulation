#pragma once

#include "ParticleData.h"
#include "Window.h"
#include "Grid.h"

class Brush
{
public:
	Brush();
	~Brush();

	Particle GetSelectedParticle(ParticleSelection selection);
	void MouseInput(Window window, Grid* grid);
	void SelectionInput(Window window, Grid* grid);

private:
	ParticleSelection selectedParticle = Sand;

};
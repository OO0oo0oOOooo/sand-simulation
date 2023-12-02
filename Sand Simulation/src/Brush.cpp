#include "Brush.h"

namespace Brush
{
	Cell selectedParticle = ParticleSand;
	int brushSize = 1;

	void MouseInput(Window window, World* world)
	{
		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			world->EditCell(Input::mousePosition, selectedParticle);
			// 
		}

		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			world->EditCell(Input::mousePosition, ParticleAir);

		}
	}

	void SelectionInput(Window window)
	{
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.Close();
		}

		if (Input::IsKeyPressed(GLFW_KEY_1))
		{
			selectedParticle = ParticleSand;
		}

		if (Input::IsKeyPressed(GLFW_KEY_2))
		{
			selectedParticle = ParticleWater;
		}

		if (Input::IsKeyPressed(GLFW_KEY_3))
		{
			selectedParticle = ParticleRock;
		}

		if (Input::IsKeyPressed(GLFW_KEY_4))
		{
			selectedParticle = ParticleWood;
		}

		if (Input::IsKeyPressed(GLFW_KEY_5))
		{
			selectedParticle = ParticleMetal;
		}
	}
}
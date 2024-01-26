#include "Brush.h"

namespace Brush
{
	Cell selectedParticle = SAND;
	int brushSize = 1;

	void MouseInput(Window window, World* world)
	{
		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			world->EditCell(Input::mousePosition, selectedParticle);
		}

		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			world->EditCell(Input::mousePosition, AIR);

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
			selectedParticle = STONE;
		}

		if (Input::IsKeyPressed(GLFW_KEY_2))
		{
			selectedParticle = DIRT;
		}

		if (Input::IsKeyPressed(GLFW_KEY_3))
		{
			selectedParticle = SAND;
		}

		if (Input::IsKeyPressed(GLFW_KEY_4))
		{
			selectedParticle = WATER;
		}

		if (Input::IsKeyPressed(GLFW_KEY_5))
		{
			selectedParticle = LAVA;
		}

		if (Input::IsKeyPressed(GLFW_KEY_6))
		{
			selectedParticle = STEAM;
		}
	}
}
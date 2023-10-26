#include "Brush.h"

namespace Brush
{
	ParticleSelection selectedParticle = Sand;

	Particle GetSelectedParticle(ParticleSelection selection)
	{

		switch (selection)
		{
		case Void:
			return ParticleVoid;

		case Air:
			return ParticleAir;

		case Sand:
			return ParticleSand;

		case Water:
			return ParticleWater;

		case Rock:
			return ParticleRock;

		case Wood:
			return ParticleWood;

		case Metal:
			return ParticleMetal;

		case Gunpowder:
			return ParticleGunpowder;

		default:
			return ParticleVoid;
			break;
		}
	}

	void MouseInput(Window window, Grid* grid)
	{
		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			glm::ivec2 index = grid->GetCellIndex(Input::normalizedMousePosition);
			//std::cout << "x: " << Input::normalizedMousePosition.x << " y: " << Input::normalizedMousePosition.y << std::endl;
			//std::cout << "Tile X: " << index.x << " Tile Y: " << index.y << std::endl;

			if (index.x > grid->GridWidth || index.x < 0)
				return;

			if (index.y > grid->GridHeight || index.y < 0)
				return;

			grid->SetCell((int)index.x, (int)index.y, GetSelectedParticle(selectedParticle));
		}
	}

	void SelectionInput(Window window, Grid* grid)
	{
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.Close();
		}

		if (Input::IsKeyPressed(GLFW_KEY_1))
		{
			selectedParticle = Sand;
		}

		if (Input::IsKeyPressed(GLFW_KEY_2))
		{
			selectedParticle = Water;
		}

		if (Input::IsKeyPressed(GLFW_KEY_3))
		{
			selectedParticle = Rock;
		}

		if (Input::IsKeyPressed(GLFW_KEY_4))
		{
			selectedParticle = Wood;
		}

		if (Input::IsKeyPressed(GLFW_KEY_5))
		{
			selectedParticle = Metal;
		}
	}
}
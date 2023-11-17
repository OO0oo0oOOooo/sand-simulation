#include "Brush.h"

namespace Brush
{
	Cell selectedParticle = ParticleSand;
	int brushSize = 1;

	void MouseInput(Window window, Grid* grid, QuadTreeObject* quadTreeObject)
	{
		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			quadTreeObject->Insert(Input::mousePosition, selectedParticle);
		}

		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			quadTreeObject->Remove(glm::vec2(Input::mousePosition));
		}
	}

	//void MouseInput(Window window, Grid* grid, QuadTreeObject* quadTreeObject)
	//{
	//	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	//	{
	//		glm::ivec2 index = grid->GetCellIndex(Input::normalizedMousePosition);
	//		//std::cout << "x: " << Input::normalizedMousePosition.x << " y: " << Input::normalizedMousePosition.y << std::endl;
	//		//std::cout << "Tile X: " << index.x << " Tile Y: " << index.y << std::endl;

	//		int rx = rand() % (2 * brushSize + 1) - brushSize;
	//		int ry = rand() % (2 * brushSize + 1) - brushSize;

	//		index += glm::ivec2(rx, ry);

	//		if (index.x > grid->GridWidth || index.x < 0)
	//			return;

	//		if (index.y > grid->GridHeight || index.y < 0)
	//			return;

	//		grid->SetCell((int)index.x, (int)index.y, selectedParticle);
	//		quadTreeObject->Insert(glm::vec2(Input::mousePosition.x, Input::mousePosition.y), selectedParticle);

	//	}
	//}

	void SelectionInput(Window window, Grid* grid)
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
#include "Brush.h"


// Paint
void Brush::MouseInput(Window window, World* world)
{
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		world->EditElementAtPixel(Input::mousePosition, _selected);
	}

	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		world->EditElementAtPixel(Input::mousePosition, 0);

	}
}

// SelectElement
void Brush::SelectionInput(Window window)
{
	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		window.Close();
	}

	//if (Input::IsKeyPressed(GLFW_KEY_1))
	//{
	//	selected = 1;
	//}

	//if (Input::IsKeyPressed(GLFW_KEY_2))
	//{
	//	selected = 2;
	//}

	if (Input::IsKeyPressed(GLFW_KEY_3))
	{
		_selected = 3;
	}

	//if (Input::IsKeyPressed(GLFW_KEY_4))
	//{
	//	selected = 4;
	//}

	//if (Input::IsKeyPressed(GLFW_KEY_5))
	//{
	//	selected = 5;
	//}

	//if (Input::IsKeyPressed(GLFW_KEY_6))
	//{
	//	selected = 6;
	//}
}


// SelectBrush


// IMGUI
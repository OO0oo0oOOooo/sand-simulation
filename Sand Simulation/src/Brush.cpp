#include "Brush.h"

void Brush::Paint(Window window, World* world)
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

void Brush::SelectElement(Window window)
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

void Brush::ChangeBrush()
{
	if (Input::IsKeyPressed(GLFW_KEY_TAB))
	{
		_brushType++;
	}

	if (_brushType > 1)
		_brushType = 0;
	
}

void Brush::ChangeBrushSize()
{
	int mouseScroll = Input::mouseScroll.y;

	if (Input::mouseScroll.y > mouseScroll)
	{
		_brushSize++;
	}

	if (Input::mouseScroll.y < mouseScroll)
	{
		_brushSize--;
	}

	if (_brushSize > 10)
		_brushSize = 10;

	if (_brushSize < 0)
		_brushSize = 1;

}


// SelectBrush


// IMGUI
//void Brush::DrawGUI()
//{
//	{
//		ImGui::Begin("Brush");
//
//		ImGui::Text("Brush Size");
//		ImGui::SliderInt("Size", &_brushSize, 1, 10);
//
//		ImGui::Text("Selected Element");
//		ImGui::SliderInt("Element", &_selected, 1, 5);
//
//		ImGui::End();
//	}
//}
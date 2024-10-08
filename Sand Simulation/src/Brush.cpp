#include "Brush.h"
#include "Events/EventManager.h"

Brush::Brush(World* world) : m_World(world)
{
	EventManager::GetInstance().MouseButtonDownEvent += std::bind(&Brush::BeginPaint, this, std::placeholders::_1);
	EventManager::GetInstance().MouseButtonUpEvent += std::bind(&Brush::EndPaint, this, std::placeholders::_1);
	EventManager::GetInstance().MouseMoveEvent += std::bind(&Brush::UpdateMousePosition, this, std::placeholders::_1, std::placeholders::_2); //std::bind(&Brush::Paint, this, std::placeholders::_1);
}

void Brush::UpdateMousePosition(int x, int y)
{
	m_MousePosition = { x, y };
}

void Brush::BeginPaint(int key)
{
	if(key == 0)
		m_Draw = true;
	else if(key == 1)
		m_Erase = true;
}

void Brush::EndPaint(int key)
{
	if (key == 0)
		m_Draw = false;
	else if (key == 1)
		m_Erase = false;
}

void Brush::Paint()
{
	if(m_Draw)
		m_World->EditElementAtPixel(m_MousePosition, m_Selected);
	else if(m_Erase)
		m_World->EditElementAtPixel(m_MousePosition, 0);
}

//void Brush::SelectElement(Window window)
//{
//	//if (Input::IsKeyPressed(GLFW_KEY_1))
//	//{
//	//	selected = 1;
//	//}
//
//	//if (Input::IsKeyPressed(GLFW_KEY_2))
//	//{
//	//	selected = 2;
//	//}
//
//	//if (Input::IsKeyPressed(GLFW_KEY_3))
//	//{
//	//	m_Selected = 3;
//	//}
//
//	//if (Input::IsKeyPressed(GLFW_KEY_4))
//	//{
//	//	selected = 4;
//	//}
//
//	//if (Input::IsKeyPressed(GLFW_KEY_5))
//	//{
//	//	selected = 5;
//	//}
//
//	//if (Input::IsKeyPressed(GLFW_KEY_6))
//	//{
//	//	selected = 6;
//	//}
//}


//void Brush::ChangeBrush()
//{
//	if (Input::IsKeyPressed(GLFW_KEY_TAB))
//	{
//		_brushType++;
//	}
//
//	if (_brushType > 1)
//		_brushType = 0;
//	
//}
//
//void Brush::ChangeBrushSize()
//{
//	int mouseScroll = Input::mouseScroll.y;
//
//	if (Input::mouseScroll.y > mouseScroll)
//	{
//		_brushSize++;
//	}
//
//	if (Input::mouseScroll.y < mouseScroll)
//	{
//		_brushSize--;
//	}
//
//	if (_brushSize > 10)
//		_brushSize = 10;
//
//	if (_brushSize < 0)
//		_brushSize = 1;
//
//}


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
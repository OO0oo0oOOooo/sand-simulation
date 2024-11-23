#pragma once

#include "Window.h"
#include "Rendering/Renderer.h"
#include "Rendering/Scene.h"

#include "Time.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	Window m_Window;
	Renderer m_Renderer;
	Scene m_Scene;
	//Brush m_Brush;
};
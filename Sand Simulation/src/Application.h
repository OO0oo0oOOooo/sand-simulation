#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	void InitGLFW();
	void InitImGui();

private:
	Window m_Window;
	//Renderer m_Renderer;
	//Game m_Game;
	//glm::uvec2 m_WindowStartSize;
};
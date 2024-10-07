#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Renderer.h"

#include "Time.h"
#include "World.h"
#include "Brush.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	Window* m_Window;
	Renderer* m_Renderer;
	World* m_World;
	Brush* m_Brush;

	glm::uvec2 m_WindowStartSize = { 1920, 1080 };
};
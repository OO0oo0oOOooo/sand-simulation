#pragma once

#include "Window.h"
#include "Rendering/Renderer.h"
#include "Core/Scene.h"

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
};

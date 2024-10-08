#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include "Events/EventManager.h"

#include <iostream>

class Window {
public:
	Window(glm::uvec2 windowSize, const char* title);
	~Window();
	
	void OnUpdate();
	void Close();

	inline int GetWidth() { return m_WindowWidth; }
	inline int GetHeight() { return m_WindowHeight; }
	inline const char* GetTitle() { return m_Title; }
	inline GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

private:
	void Init();
	void Shutdown();

	int m_WindowWidth;
	int m_WindowHeight;
	const char* m_Title;
	GLFWwindow* m_NativeWindow;
};
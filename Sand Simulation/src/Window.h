#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Window {
public:
	Window(int width, int height, const char* title);
	void Close();

	inline int GetWidth() { return m_WindowWidth; }
	inline int GetHeight() { return m_WindowHeight; }
	inline glm::vec2 GetAspectRatio() { return m_AspectRatio; }
	inline const char* GetTitle() { return m_Title; }
	inline GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

		win->m_WindowWidth = width;
		win->m_WindowHeight = height;
		win->m_AspectRatio = glm::vec2((float)width / 1920.0f, (float)height / 1080.0f);
	}

private:
	int m_WindowWidth;
	int m_WindowHeight;
	const char* m_Title;
	GLFWwindow* m_NativeWindow;
	glm::vec2 m_AspectRatio;
};
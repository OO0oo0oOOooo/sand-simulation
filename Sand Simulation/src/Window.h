#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, const char* title);
	~Window();
	void Close();

	inline int GetWidth() { return m_WindowWidth; }
	inline int GetHeight() { return m_WindowHeight; }
	inline const char* GetTitle() { return m_Title; }
	inline GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

private:
	int m_WindowWidth;
	int m_WindowHeight;
	const char* m_Title;
	GLFWwindow* m_NativeWindow;
};
#include "Window.h"

Window::Window(int width, int height, const char* title)
	: m_WindowWidth(width), m_WindowHeight(height), m_Title(title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	GLFWmonitor* monitor = NULL; // glfwGetPrimaryMonitor();
	m_NativeWindow = glfwCreateWindow(width, height, title, monitor, NULL);
	glfwMakeContextCurrent(m_NativeWindow);

	if (!m_NativeWindow)
	{
		glfwTerminate();
	}
}

Window::~Window()
{
}

void Window::Close()
{
	if(m_NativeWindow != nullptr)
		glfwSetWindowShouldClose(m_NativeWindow, GLFW_TRUE);
}
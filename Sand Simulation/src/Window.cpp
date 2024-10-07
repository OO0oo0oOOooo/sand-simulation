#include "Window.h"
#include "Input.h"
#include "Events/EventManager.h"

Window::Window(glm::uvec2 windowSize, const char* title)
	: m_WindowWidth(windowSize.x), m_WindowHeight(windowSize.y), m_Title(title), m_AspectRatio(glm::vec2((float)windowSize.x / 1920.0f, (float)windowSize.y / 1080.0f))
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor(); //nullptr;
	m_NativeWindow = glfwCreateWindow(windowSize.x, windowSize.y, title, monitor, NULL);
	if (!m_NativeWindow)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_NativeWindow);
	//glfwSwapInterval(0);

	glfwSetWindowUserPointer(m_NativeWindow, this);

	glfwSetFramebufferSizeCallback(m_NativeWindow, framebuffer_size_callback);

	EventManager::GetInstance().WindowCloseEvent += std::bind(&Window::Close, this);

	Input::SetupKeyInputs(GetNativeWindow());
}

void Window::Close()
{
	if (m_NativeWindow != nullptr)
		glfwSetWindowShouldClose(m_NativeWindow, GLFW_TRUE);
}


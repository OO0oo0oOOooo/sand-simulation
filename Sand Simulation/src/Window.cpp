#include "Window.h"

Window::Window(glm::uvec2 windowSize, const char* title)
	: m_WindowWidth(windowSize.x), m_WindowHeight(windowSize.y), m_Title(title)
{
	Init();

	//EventManager::GetInstance().WindowCloseEvent += std::bind(&Window::Close, this);
}

Window::~Window()
{
	Shutdown();
}

void Window::Init()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		assert(false);
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor(); //nullptr;
	m_NativeWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_Title, monitor, NULL);
	if (!m_NativeWindow)
	{
		glfwTerminate();
	}

	// Context
	glfwMakeContextCurrent(m_NativeWindow);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		assert(false);
		exit(EXIT_FAILURE);
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Callbacks
	glfwSetWindowUserPointer(m_NativeWindow, this);
	//glfwSwapInterval(0); // VSync

	glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
	{
		EventManager::GetInstance().WindowResizeEvent(width, height);
	});

	glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window)
	{
		EventManager::GetInstance().WindowCloseEvent();
	});

	glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		EventManager::GetInstance().KeyEvent(key, scancode, action, mods);

		switch (action)
		{
		case GLFW_PRESS:
			EventManager::GetInstance().KeyDownEvent(key);
			break;
		case GLFW_RELEASE:
			EventManager::GetInstance().KeyUpEvent(key);
			break;
		case GLFW_REPEAT:
			EventManager::GetInstance().KeyRepeatEvent(key);
			break;
		}
	});

	glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		EventManager::GetInstance().MouseButtonEvent(button, action, mods);

		switch (action)
		{
		case GLFW_PRESS:
			EventManager::GetInstance().MouseButtonDownEvent(button);
			break;
		case GLFW_RELEASE:
			EventManager::GetInstance().MouseButtonUpEvent(button);
			break;
		case GLFW_REPEAT:
			EventManager::GetInstance().MouseButtonRepeatEvent(button);
			break;
		}
	});

	glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

		EventManager::GetInstance().MouseMoveEvent(xpos, win->GetHeight() - ypos);
	});

	glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset)
	{
		EventManager::GetInstance().MouseScrollEvent(xoffset, yoffset);
	});

	/*glfwSetFramebufferSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

		win->m_WindowWidth = width;
		win->m_WindowHeight = height;
	});*/
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_NativeWindow);
}

void Window::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_NativeWindow);
}

void Window::Close()
{
	if (m_NativeWindow != nullptr)
		glfwSetWindowShouldClose(m_NativeWindow, GLFW_TRUE);
}


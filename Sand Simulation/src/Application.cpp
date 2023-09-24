#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include "Input.h"

void testInput(GLFWwindow* window)
{
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		std::cout << "LMB pressed" << std::endl;
	}

    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    unsigned int windowWidth = 1280;
    unsigned int windowHeight = 720;

    GLFWmonitor* monitor = NULL; // glfwGetPrimaryMonitor();
    const GLFWvidmode* mode;

    if (monitor != NULL)
    {
        mode = glfwGetVideoMode(monitor);
        windowWidth = mode->width;
        windowHeight = mode->height;
    }

    window = glfwCreateWindow(windowWidth, windowHeight, "Sand Simulation", monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Input::SetupKeyInputs(window);

 //   std::vector<float> positions = {
	//	-1.0f, -1.0f, // 0
	//	 0.0f,  1.0f, // 1
	//	 1.0f, -1.0f, // 2
	//};

 //   std::vector<unsigned int> indices = {
 //       0, 1, 2
	//};

 //   unsigned int vao;
 //   glGenVertexArrays(1, &vao);
 //   glBindVertexArray(vao);

 //   unsigned int VertexBuffer;
 //   glGenBuffers(1, &VertexBuffer);
 //   glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
 //   glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

 //   unsigned int IndexBuffer;
 //   glGenBuffers(1, &IndexBuffer);
 //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
 //   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
 //   
 //   glEnableVertexAttribArray(0);
 //   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);    

    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        testInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
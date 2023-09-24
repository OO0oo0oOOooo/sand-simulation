#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include "Window.h"
#include "Input.h"

// TODO:
// - Shader class
// - Rendering class

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

void testInput(Window window)
{
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		std::cout << "LMB pressed" << std::endl;
	}

    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.Close();
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    // This might be copying the window object, but I'm not sure
    Window window(windowWidth, windowHeight, "Sand Simulation");
    GLFWwindow* glwindow = window.GetNativeWindow();

    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Input::SetupKeyInputs(glwindow);

    Vertex vertices[] = {
        { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(0.9f, 0.8f, 0.2f, 1.0f) },
        { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec4(0.9f, 0.2f, 0.8f, 1.0f) },
        { glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec4(0.2f, 0.9f, 0.8f, 1.0f) },
        { glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec4(0.5f, 0.2f, 0.5f, 1.0f) },
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 12);
    glEnableVertexAttribArray(1);

    unsigned int indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSource = R"(
		#version 430 core

		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;

        out vec4 v_Color;

		void main()
		{
			v_Color = a_Color;

			gl_Position = vec4(a_Position, 1.0);
		}
	)";

    const char* fragmentShaderSource = R"(
        #version 430 core

        out vec4 FragColor;

		in vec4 v_Color;

        void main()
        {
           FragColor = v_Color;
        }
    )";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        testInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
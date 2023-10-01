#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Window.h"
#include "Input.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    Shader shader;

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, -0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    model = glm::scale(model, glm::vec3(100.0f));

    glm::mat4 VP = proj * view;

    shader.Bind();
    shader.SetUniformMat4f("u_ViewProjection", VP);
    shader.SetUniformMat4f("u_Transform", model);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        testInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
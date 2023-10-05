#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "Window.h"
#include "Input.h"
#include "Grid.h"

#include "Shader.h"
#include "vertexBuffer.h"
#include "IndexBuffer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// TODO:
// - Rendering class
// - Grid class
// - Update loop

// - Chunks
// - each chunk has a grid map. 2D array of bytes, 0 air, 1 sand, 2 water, 3 stone, 4 dirt, 5 grass

// - tick and late tick
// - every tick, update the grid map
// - every late tick, render the new grid map if it has changed

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

void testInput(Window window, Grid grid)
{
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		glm::vec2 mouse = grid.GetTileIndexFromPos(Input::mousePosition);
		std::cout << "Tile at mouse pos: " << mouse.x << ", " << mouse.y << std::endl;

		grid.TerrainMap[mouse.x][mouse.y].type = 1;
        grid.UpdateArrays();
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
    Grid grid;
    grid.UpdateArrays();

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 12);
    glEnableVertexAttribArray(1);

    VertexBuffer vb(grid.m_Vertices.data(), grid.m_Vertices.size() * sizeof(Vertex));
    IndexBuffer ib(grid.m_Indices.data(), grid.m_Indices.size());
    Shader shader;

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader.Bind();
    shader.SetUniformMat4f("u_ViewProjection", VP);
    shader.SetUniformMat4f("u_Transform", model);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        testInput(window, grid);

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vao);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, grid.m_Indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
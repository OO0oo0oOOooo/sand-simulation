#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"

// TODO:
// - Update loop

// - Chunks
// - each chunk has a grid map. 2D array of bytes, 0 air, 1 sand, 2 water, 3 stone, 4 dirt, 5 grass

// - tick and late tick
// - every tick, update the grid map
// - every late tick, render the new grid map if it has changed

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

void testInput(Window window, Renderer* renderer)
{
    
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		glm::vec2 mouse = renderer->GetTileIndexFromPos(Input::mousePosition);
		std::cout << "Tile at mouse pos: " << mouse.x << ", " << mouse.y << std::endl;

		renderer->TerrainMap[mouse.x][mouse.y].type = 0;
        renderer->UpdateBuffers();
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

    Renderer* renderer = new Renderer();
    Input::SetupKeyInputs(glwindow);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        testInput(window, renderer);

        renderer->Clear();
        renderer->Draw();

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    delete renderer;
    glfwTerminate();
    return 0;
}
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

unsigned int selectedParticle = 1;

Particle GetSelectedParticle()
{
    switch (selectedParticle)
    {
    case 0:
        return { 0, { 0.0f, 0.0f, 0.0f, 0.0f } };

    case 1:
        return { 1, { 0.9f, 0.8f, 0.2f, 1.0f } };

    case 2:
        return { 2, { 0.2f, 0.9f, 0.8f, 1.0f } };

    case 3:
		return { 3, { 0.5f, 0.2f, 0.5f, 1.0f } };

    case 4:
        return { 4, { 0.4f, 0.2f, 0.1f, 1.0f } };

    case 5:
        return { 5, { 0.3f, 0.3f, 0.3f, 1.0f } };

    case 6:
        return { 6, { 0.2f, 0.2f, 0.2f, 1.0f } };

    default:
        break;
    }
}

void testInput(Window window, Renderer* renderer)
{
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		glm::vec2 mouse = renderer->GetTileIndexFromPos(Input::mousePosition);
		//std::cout << "Tile at mouse pos: " << mouse.x << ", " << mouse.y << std::endl;

        if (mouse.x > renderer->tilesX || mouse.x < 0)
            return;

        if (mouse.y > renderer->tilesY || mouse.y < 0)
            return;

        renderer->TerrainMap[(unsigned int)mouse.x][(unsigned int)mouse.y] = GetSelectedParticle();
        renderer->UpdateBuffers();
	}

    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.Close();
    }

    if (Input::IsKeyPressed(GLFW_KEY_1))
    {
        selectedParticle = 1;
    }

    if (Input::IsKeyPressed(GLFW_KEY_2))
    {
        selectedParticle = 2;
    }

    if (Input::IsKeyPressed(GLFW_KEY_3))
    {
        selectedParticle = 3;
    }

    if (Input::IsKeyPressed(GLFW_KEY_4))
    {
        selectedParticle = 4;
    }

    if (Input::IsKeyPressed(GLFW_KEY_5))
    {
        selectedParticle = 5;
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

        // Update each cell in grid
        //for (int x = 0; x < renderer->tilesX; x++)
        //    for (int y = 0; y < renderer->tilesY; y++)

        // Update particles
        // UpdateSand()
		// UpdateWater()

        renderer->Clear();
        renderer->Draw();

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    delete renderer;
    glfwTerminate();
    return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Grid.h"

#include "ParticleData.h"

// TODO:
// - Update loop
// - tick and late tick
//
// - Particle Brush
// - Particle Selection
// - Particle Selection UI
// - 

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;
unsigned int gridResolution = 64;

ParticleSelection selectedParticle = Sand;

Particle GetSelectedParticle(ParticleSelection selection)
{
	switch (selection)
	{
	case Void:
		return ParticleVoid;

	case Air:
		return ParticleAir;

	case Sand:
		return ParticleSand;

	case Water:
		return ParticleWater;

	case Rock:
		return ParticleRock;

	case Wood:
		return ParticleWood;

	case Metal:
		return ParticleMetal;

	case Gunpowder:
		return ParticleGunpowder;

	default:
		return ParticleVoid;
		break;
	}
}

void TestInput(Window window, Renderer* renderer, Grid* grid)
{
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse = grid->GetCellIndex(Input::mousePosition);
		std::cout << "Tile at mouse pos: " << mouse.x << ", " << mouse.y << std::endl;

		if (mouse.x > grid->GridWidth || mouse.x < 0)
			return;

		if (mouse.y > grid->GridHeight || mouse.y < 0)
			return;

		grid->SetCell((int)mouse.x, (int)mouse.y, GetSelectedParticle(selectedParticle));
	}

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		window.Close();
	}

	if (Input::IsKeyPressed(GLFW_KEY_1))
	{
		selectedParticle = Sand;
	}

	if (Input::IsKeyPressed(GLFW_KEY_2))
	{
		selectedParticle = Water;
	}

	if (Input::IsKeyPressed(GLFW_KEY_3))
	{
		selectedParticle = Rock;
	}

	if (Input::IsKeyPressed(GLFW_KEY_4))
	{
		selectedParticle = Wood;
	}

	if (Input::IsKeyPressed(GLFW_KEY_5))
	{
		selectedParticle = Metal;
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
	Grid* grid = new Grid(windowWidth, windowHeight, gridResolution);

	grid->InitGrid();
	renderer->UpdateBuffers(grid);

    Input::SetupKeyInputs(glwindow);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        TestInput(window, renderer, grid);

		grid->UpdateGrid();
		renderer->UpdateBuffers(grid);

        renderer->Clear();
        renderer->Draw();

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    delete renderer;
	delete grid;
    glfwTerminate();
    return 0;
}


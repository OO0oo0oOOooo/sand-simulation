#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Grid.h"

#include "ParticleData.h"

// TODO:
// - ImGUI
// 
// - Update loop
// - tick and late tick
//
// - Particle Brush
// - Particle Selection
// - Particle Selection UI
//
// - Move ParticleSelection out of Application
// - Move TestInput out of Application

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

void TestInput(Window window, Grid* grid)
{
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::ivec2 index = grid->GetCellIndex(Input::normalizedMousePosition);
		//std::cout << "x: " << Input::normalizedMousePosition.x << " y: " << Input::normalizedMousePosition.y << std::endl;
		//std::cout << "Tile X: " << index.x << " Tile Y: " << index.y << std::endl;

		if (index.x > grid->GridWidth || index.x < 0)
			return;

		if (index.y > grid->GridHeight || index.y < 0)
			return;

		grid->SetCell((int)index.x, (int)index.y, GetSelectedParticle(selectedParticle));
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

    Renderer* renderer = new Renderer(windowWidth, windowHeight);
	Grid* grid = new Grid(windowWidth, windowHeight, gridResolution);

	grid->InitGrid();
	renderer->UpdateBuffers(grid);

    Input::SetupKeyInputs(glwindow);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(glwindow))
    {
        TestInput(window, grid);

		grid->UpdateGrid();
		renderer->UpdateBuffers(grid);

        //renderer->Clear();
        renderer->Draw();

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    delete renderer;
	delete grid;
    glfwTerminate();
    return 0;
}


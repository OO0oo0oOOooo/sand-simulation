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

// - Chunks
// - each chunk has a grid map. 2D array of bytes, 0 air, 1 sand, 2 water, 3 stone, 4 dirt, 5 grass

// - tick and late tick
// - every tick, update the grid map
// - every late tick, render the new grid map if it has changed

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
		renderer->UpdateBuffers(grid);
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

//Particle GetParticle(Renderer* renderer, int x, int y)
//{
//	return renderer->TerrainMap[x][y];
//}
//
//void SetParticle(Renderer* renderer, int x, int y, Particle particle)
//{
//	renderer->TerrainMap[x][y] = particle;
//}
//
//void UpdateSand(Renderer* renderer, int x, int y)
//{
//	if (y < 0)
//		return;
//
//	if (GetParticle(renderer, x, y).type == ParticleSand.type)
//	{
//
//		if (GetParticle(renderer, x, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(renderer, x, y, ParticleAir);
//			SetParticle(renderer, x, y - 1, ParticleSand);
//		}
//		else if (GetParticle(renderer, x + 1, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(renderer, x, y, ParticleAir);
//			SetParticle(renderer, x + 1, y - 1, ParticleSand);
//		}
//		else if (GetParticle(renderer, x - 1, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(renderer, x, y, ParticleAir);
//			SetParticle(renderer, x - 1, y - 1, ParticleSand);
//		}
//
//	}
//}

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

        // // Update each cell in grid
		// for (int x = 0; x < renderer->tilesX; x++)
		// {
		//	 for (int y = 0; y < renderer->tilesY; y++)
		//	 {
		//		 // UpdateSand(renderer, x, y);
		//		 // UpdateWater()
		//	 }
		// }

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


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Grid.h"
#include "Brush.h"

//#include "ParticleData.h"

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
        Brush::MouseInput(window, grid);
        Brush::SelectionInput(window, grid);

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


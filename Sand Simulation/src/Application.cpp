#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Grid.h"
#include "Brush.h"

#include <iostream>

// TODO:
// [ ] Update loop
// [ ] tick and late tick
//
// UI:
// [ ] Particle Selection UI
//
// Optimizations:
// [ ] QuadTree
// [ ] Chunks
// [ ] Compute Shaders
// [ ] Multithreading
// 
// [ ] glBufferSubData instead of glBufferData
//  - Set positions
//  - Add/Remove to DirtyCells Vector
// 
// [x] Use a flat array instead of a 2D array
// [x] UpdateBuffers with dirty flag
//
// Reactions:
// [ ] Wood + Fire = Fire
// [ ] Water + Lava = Stone
//
// Effects:
// [ ] Lighting
//  - Flood Fill
// [ ] Texturing Groups


unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;
unsigned int gridResolution = 256;

int main(void)
{
    if (!glfwInit())
        return -1;

    Window window(windowWidth, windowHeight, "Sand Simulation");
    GLFWwindow* glwindow = window.GetNativeWindow();

    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Renderer* renderer = new Renderer(windowWidth, windowHeight);
	Grid* grid = new Grid(windowWidth, windowHeight, gridResolution);

	grid->InitGrid();
    renderer->InitBuffers(grid);
	renderer->UpdateBuffers(grid);

    Input::SetupKeyInputs(glwindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glwindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    bool show_demo_window = false;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(glwindow))
    {
        Brush::MouseInput(window, grid);
        Brush::SelectionInput(window, grid);

		grid->UpdateGrid();
		renderer->UpdateBuffers(grid);
        renderer->Draw();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //if(show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

        {
            ImGui::Begin("FPS");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    delete renderer;
	delete grid;
    glfwTerminate();
    return 0;
}


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Brush.h"

//#include "Grid.h"
//#include "Quadtree.h"
//#include "QuadTreeObject.h"
#include "World.h"

//#include <iostream>

// TODO:
// 
// [ ] STPImage
// [ ] Replace Grid with QuadTree
// [ ] Check QuadTree cells for updates
// [ ] Seperate QuadTree debug mesh from QuadTreeGridMesh
// [ ] Quadtree features/optimizations
// 
// [ ] Update loop
// [ ] tick and late tick
//
// UI:
// [ ] Particle Selection UI
//
// Optimizations:
// [ ] Dirty Quads
// [ ] Multithreading Chunks
// [ ] Instanced Rendering
// [ ] Compute Shaders
// [ ] Reduce size of buffer (Build Quads on gpu)
// 
// 
// World:
// [ ] Update only dirty chunks
// [ ] UpdateCells across borders
// [ ] Dirty Quads
// [ ] aspect ratio variable
// 
// Chunks:
// [ ]
// 
// Grid:
// [ ] Build mesh inside grid class
// [ ] Get rid of DirtyCells vector
//
// Reactions:
// [ ] Wood + Fire = Fire
// [ ] Water + Lava = Stone
//
// Effects:
// [ ] Lighting
//      Flood Fill
//
// [ ] Texturing Groups
// [ ] Tiled textures across the world
//      Cells will get the texture for there block ID
//
// Refactoring:
// [ ] Cell.cpp doesnt do anything anymore and has a lot of comments
// [ ] Cell.h has a lot of comments

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
    World* world = new World;
    world->Render(renderer->GetShader());



    Input::SetupKeyInputs(glwindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glwindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(glwindow))
    {
        Brush::MouseInput(window, world);
        Brush::SelectionInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        world->Update(0.2f);
        world->Render(renderer->GetShader());

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //if(true)
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
	//delete grid;
    glfwTerminate();
    return 0;
}


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ctpl/ctpl_stl.h"

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Brush.h"
#include "World.h"

#include "Time.h"

//#include <iostream>

// TODO:
// 
// [ ] ticks
// [ ] some kind of fixed update for "physics"
// 
// Multitreading:
// [x] Thread Pool
// [x] Multithreading Chunks in checkered pattern
//      4 Updates per frame
//      First I check if the chunk is dirty
//      Then I find which update the chunk is on
//      Queue the chunk to the thread pool
//      When the thread is done repeat for the second update
//
// GUI:
// [ ] Particle Selection UI
//
// Optimizations:
// [x] Dirty Rect per chunk
// [x] Multithreading Chunks in checkered pattern
// [ ] Instanced Rendering
// [ ] Compute Shaders
// [ ] Reduce size of buffer (Build Quads on gpu)
// [ ] Dont draw air
// [ ] Dirty Chunks
// [ ] Create a quad with a texture for the entire screen then draw each cell as a pixel on the quad
// 
// World:
// [ ] Multithreading doesnt update the mesh of chunks that cross into the next chunk properly.
// - Temporary unordered set of chunks that get updated when each thread is done
// 
// Chunks:
// [ ] Velocity is wacky right now. I need a fixed timestep and to fix preformance issues
// [ ] Check cells in between the start and end position
// [ ] Try recreating the entire mesh after each thread is done that way i only need to manipulate the chunk data inside of the threads
// 
// Dirty Rect:
// Think of a more efficient way to grow and shrink the dirty rect
//
// Effects:
// [ ] Lighting
//      Flood Fill
//
// [ ] Texturing Groups
// [ ] Tiled textures across the world
//      Cells will get the texture for there block ID
// 
// Bugs:
// [ ] Falling sand doesnt draw on chunkborders
// [ ] memory leak for drawing debug chunk boarders and debug dirty quads
// [ ] Water is weird and always flows left
//
// Refactoring:
// [ ] Cell.cpp doesnt do anything
// [ ] Cell.h has a lot of comments

unsigned int windowWidth = 1920;
unsigned int windowHeight = 1080;
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

    ctpl::thread_pool* threadPool = new ctpl::thread_pool(4);
    Renderer* renderer = new Renderer(windowWidth, windowHeight);
    World* world = new World(threadPool);
    
    Input::SetupKeyInputs(glwindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glwindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(glwindow))
    {
        Time::Update();

        Brush::MouseInput(window, world);
        Brush::SelectionInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        world->Update(renderer->GetShader());

        // This causes a memory leak because it is poorly designed. It recreates the mesh every frame.
        // world->DrawChunkBorders(renderer->GetShader());
        
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
    delete world;
    glfwTerminate();
    return 0;
}


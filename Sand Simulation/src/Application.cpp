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
// [ ] STPImage
// 
// [ ] Update loop
// [ ] Delta Time
// [ ] tick and late tick
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
// UI:
// [ ] Particle Selection UI
//
// Optimizations:
// [ ] Dirty Rect per chunk
// [x] Multithreading Chunks in checkered pattern
// [ ] Instanced Rendering
// [ ] Compute Shaders
// [ ] Reduce size of buffer (Build Quads on gpu)
// [ ] Dont draw air
// 
// World:
// 
// Chunks:
// 
// Dirty Rect:
// [ ] Bounds
// [ ] Update through every cell in the bounds
// - If i want to add a cell to the dirty quad i just have to check if it is inside the bounds
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
// [ ] Huge memory leak with chunk multithreading
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
        Time::Update();

        Brush::MouseInput(window, world);
        Brush::SelectionInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        world->Update();
        world->Render(renderer->GetShader());
        world->DrawChunkBorders(renderer->GetShader());

        

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


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ctpl/ctpl_stl.h"

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Time.h"

#include "Brush.h"
#include "World.h"

unsigned int windowWidth = 1920;
unsigned int windowHeight = 1080;

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
    
    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glwindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // Game
    ctpl::thread_pool* threadPool = new ctpl::thread_pool(4);
    World* world = new World(threadPool);
    Brush brush(world);
    Input::SetupKeyInputs(glwindow);

    while (!glfwWindowShouldClose(glwindow))
    {
        Time::Update();
        glClear(GL_COLOR_BUFFER_BIT);

        brush.Paint();

        world->Update(renderer->GetShader());

        world->DebugDrawInit();
        world->DebugDraw(renderer->GetShader());

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

    delete threadPool;
    delete renderer;
    delete world;

    glfwTerminate();
    return 0;
}

#include "Application.h"

Application::Application() : m_Window(windowWidth, windowHeight, "Sand Simulation")
{
    InitGLFW();
    InitImGui();

}

Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window.GetNativeWindow()))
    {

    }
}

void Application::InitGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void Application::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
}
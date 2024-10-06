/*
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
    
    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glwindow, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // Game
    Renderer* renderer = new Renderer(windowWidth, windowHeight);
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
*/

#include "Application.h"

Application::Application()
{
    //InitGLFW();

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        assert(false);
        exit(EXIT_FAILURE);
    }

    m_Window = new Window(m_WindowStartSize, "Sand Simulation");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        assert(false);
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    m_Renderer = new Renderer(m_WindowStartSize.x, m_WindowStartSize.y);
    m_World = new World();
    m_Brush = new Brush(m_World);

    Input::SetupKeyInputs(m_Window->GetNativeWindow());
}

Application::~Application()
{
    delete m_Window;
    delete m_Renderer;
    delete m_World;
    delete m_Brush;

    glfwTerminate();
}

void Application::Run()
{
    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(m_Window->GetNativeWindow()))
    {
        Time::Update();
        glClear(GL_COLOR_BUFFER_BIT);

        m_Brush->Paint();

        m_World->Update(m_Renderer->GetShader());

        m_World->DebugDrawInit();
        m_World->DebugDraw(m_Renderer->GetShader());

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

        glfwSwapBuffers(m_Window->GetNativeWindow());
        glfwPollEvents();
    }
}
#include "Application.h"

Application::Application() : m_Window(), m_Renderer(m_Window.GetNativeWindow()), m_Scene(&m_Renderer) {}

Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{
    m_Scene.SubmitToRenderer();
    m_Scene.Start();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(m_Window.GetNativeWindow()))
    {
        Time::Update();
        m_Renderer.Render();
        m_Scene.Update();

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

        m_Window.OnUpdate();
    }
}
#include "Application.h"

Application::Application()
{
    m_Window = new Window(m_WindowStartSize, "Sand Simulation");
    m_Renderer = new Renderer(m_Window);
    m_World = new World();
    m_Brush = new Brush(m_World);
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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(m_Window->GetNativeWindow()))
    {
        m_Renderer->Render();

        Time::Update();

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

        m_Window->OnUpdate();
    }
}
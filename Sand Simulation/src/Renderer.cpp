#include "Renderer.h"

Renderer::Renderer(Window* window) : m_Window(window)
{
    m_Mesh = new Mesh();
    m_Shader = new Shader();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 proj = glm::ortho(0.0f, (float)m_Window->GetWidth(), 0.0f, (float)m_Window->GetHeight(), -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_ViewProjection", VP);
    m_Shader->SetUniformMat4f("u_Transform", model);
    m_Shader->SetUniform4f("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

Renderer::~Renderer()
{
    delete m_Mesh;
    delete m_Shader;
}

void Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw()
{
    m_Mesh->Draw(m_Shader);
}
#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window) : m_Window(window) {}

//Todo: Gameobjects that want to be rendered need the MeshRenderer component, this component will comunicate with the renderer.
// Currently the scene is checking all GameObjects if they have a mesh then creating a batch here if they do.
void Renderer::NewBatch(std::weak_ptr<Material> material, std::weak_ptr<VertexArray> vertexArray, std::weak_ptr<Transform> transform)
{
    Batch batch;
    batch.material = material;
    batch.vertexArray = vertexArray;
    batch.transform = transform;

    m_Batches.push_back(batch);
}

void Renderer::RenderBatches()
{
    glClear(GL_COLOR_BUFFER_BIT);

    auto it = m_Batches.begin();
    while (it != m_Batches.end())
    {
        auto materialPtr = it->material.lock();
        auto vertexArrayPtr = it->vertexArray.lock();
        auto transformPtr = it->transform.lock();

        if (materialPtr && vertexArrayPtr && transformPtr)
        {
            materialPtr->Bind(m_Camera.GetViewProjectionMatrix(), transformPtr->GetModelMatrix());
            vertexArrayPtr->Bind();

            glDrawElements(GL_TRIANGLES, vertexArrayPtr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            it++;
        }
        else
        {
            it = m_Batches.erase(it);
        }
    }
}

//void Renderer::Draw(VertexArray* vertexArray)
//{
//    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount() , GL_UNSIGNED_INT, nullptr);
//}

//void Renderer::Render()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (size_t i = 0; i < m_Batches.size(); ++i)
//    {
//        m_Batches[i].material->Bind(m_Camera.GetViewProjectionMatrix(), m_Batches[i].transform->GetModelMatrix());
//        m_Batches[i].vertexArray->Bind();
//        glDrawElements(GL_TRIANGLES, m_Batches[i].vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
//    }
//}
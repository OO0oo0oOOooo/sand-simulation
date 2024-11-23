#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window) : m_Window(window)
{
    //Todo: I think blending stuff would make more sense inside the material SetMaterialBlendMode()
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::SetViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

//Todo: Gameobjects that want to be rendered need the MeshRenderer component, this component will comunicate with the renderer.
// Currently the scene is checking all GameObjects if they have a mesh then creating a batch here if they do.
void Renderer::NewBatch(Material* material, VertexArray* vertexArray, Transform* transform)
{
    Batch batch;
    batch.material = material;
    batch.vertexArray = vertexArray;
    batch.transform = transform;

    m_Batches.push_back(batch);
}

//void Renderer::Draw(VertexArray* vertexArray)
//{
//    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount() , GL_UNSIGNED_INT, nullptr);
//}

void Renderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (size_t i = 0; i < m_Batches.size(); ++i)
    {
        m_Batches[i].material->Bind(m_Camera.GetViewProjectionMatrix(), m_Batches[i].transform->GetModelMatrix());
        m_Batches[i].vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_Batches[i].vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
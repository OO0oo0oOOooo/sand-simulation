#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(GameObject* obj) : Component(obj)
{
	// TODO: Init
}

void MeshRenderer::SetMesh(std::shared_ptr<Mesh> mesh)
{
    m_Mesh = mesh;
}

void MeshRenderer::SetMaterial(std::shared_ptr<Material> material)
{
    m_Material = material;
}

std::shared_ptr<Mesh> MeshRenderer::GetMesh() const
{
    return m_Mesh;
}

std::shared_ptr<Material> MeshRenderer::GetMaterial() const
{
    return m_Material;
}

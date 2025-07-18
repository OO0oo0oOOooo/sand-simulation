#pragma once

#include "../GameObject.h"
#include "../../Rendering/Renderer.h"
#include "Mesh.h"
#include "Material.h"

#include <memory>

//todo: this should communicate with the renderer instead of the scene doing it

class MeshRenderer : public Component
{
public:
	MeshRenderer(GameObject* obj);

	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SetMaterial(std::shared_ptr<Material> material);

	std::shared_ptr<Mesh> GetMesh() const;
	std::shared_ptr<Material> GetMaterial() const;

private:
	std::shared_ptr<Mesh> m_Mesh;
	std::shared_ptr<Material> m_Material;
};

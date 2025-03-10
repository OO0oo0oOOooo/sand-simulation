#include "Material.h"

Material::Material(GameObject* obj) : Component(obj)
{
	m_Shader = new Shader(m_ShaderId);
	m_Texture = new Texture(64 * 6, 64 * 4);
}

void Material::Bind(glm::mat4 vpMatrix, glm::mat4 modelMatrix)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_ViewProjection", vpMatrix);
	m_Shader->SetUniformMat4f("u_Transform", modelMatrix);
	m_Shader->SetUniform1i("u_Texture", 0);
}

void Material::Unbind()
{
	m_Shader->Unbind();
}

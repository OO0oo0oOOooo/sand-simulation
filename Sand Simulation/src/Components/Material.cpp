#include "Material.h"

Material::Material(GameObject* obj) : Component(obj)
{
	m_Shader = new Shader(m_ShaderId);
}

void Material::SetColor(float r, float g, float b, float a)
{

}

void Material::SetTexture(const char* texturePath)
{

}

void Material::Bind(glm::mat4 vpMatrix, glm::mat4 modelMatrix)
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_ViewProjection", vpMatrix);
	m_Shader->SetUniformMat4f("u_Transform", modelMatrix);
	m_Shader->SetUniform4f("u_Color", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void Material::Unbind()
{
	m_Shader->Unbind();
}

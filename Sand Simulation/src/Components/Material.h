#pragma once

#include "../Scene/GameObject.h"
#include "../Rendering/shader.h"

class Material : public Component
{
public:
	Material(GameObject* obj);

	void SetColor(float r, float g, float b, float a);
	void SetTexture(const char* texturePath);

	void Bind(glm::mat4 vpMatix, glm::mat4 modelMatix);
	void Unbind();

	Shader* GetShader() { return m_Shader; }

private:
	const char* m_ShaderId = "default_shader";
	Shader* m_Shader;
};
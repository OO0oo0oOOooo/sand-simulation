#pragma once

#include "../Core/GameObject.h"
#include "../Rendering/shader.h"
#include "../Rendering/Texture.h"

class Material : public Component
{
public:
	Material(GameObject* obj);

	void Bind(glm::mat4 vpMatix, glm::mat4 modelMatix);
	void Unbind();

	const Shader* GetShader() const { return m_Shader; }
	Texture* GetTexture() const { return m_Texture; }

private:
	const char* m_ShaderId = "default_shader";
	Shader* m_Shader;

	const char* m_TextureID = "blank_texture";
	Texture* m_Texture;
};
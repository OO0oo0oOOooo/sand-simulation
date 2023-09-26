#pragma once

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind();
	void Unbind();

	// Set uniforms
	// Create a .shader file and read from it
private:
	unsigned int m_RendererID;
};
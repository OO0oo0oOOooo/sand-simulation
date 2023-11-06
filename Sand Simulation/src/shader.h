#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Shader {
public:
	Shader();
	~Shader();

	void Bind();
	void Unbind();

	unsigned int CompileShader(unsigned int type, const char* filePath);

	void SetUniform1f(const char* name, float value);
	void SetUniform2f(const char* name, glm::vec2 value);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniform4f(const char* name, glm::vec4 value);

	void SetUniform1i(const char* name, int value);
	void SetUniform2i(const char* name, glm::ivec2 value);
	void SetUniform3i(const char* name, glm::ivec3 value);
	void SetUniform4i(const char* name, glm::ivec4 value);

	void SetUniformMat2f(const char* name, const glm::mat2& matrix);
	void SetUniformMat3f(const char* name, const glm::mat3& matrix);
	void SetUniformMat4f(const char* name, const glm::mat4& matrix);

private:
	unsigned int m_ProgramID;
};
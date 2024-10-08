#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Mesh.h"
#include "Window.h"

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Render();
	void Draw();

	inline Shader* GetShader() { return m_Shader; }
	
private:
	Window* m_Window;
	Mesh* m_Mesh;
	Shader* m_Shader;
};
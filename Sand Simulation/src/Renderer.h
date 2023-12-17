#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Mesh.h"

#include "Cell.h"


class Renderer
{
public:
	Renderer(int windowWidth, int windowHeight);
	~Renderer();

	void Clear() const;
	void Draw();

	inline Shader* GetShader() { return shader; }
	
private:
	Mesh* mesh;
	Shader* shader;
};
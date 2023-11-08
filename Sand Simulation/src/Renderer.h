#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Mesh.h"

#include "Cell.h"
#include "Grid.h"

class Renderer
{
public:
	Renderer(int windowWidth, int windowHeight);
	~Renderer();

	void InitBuffers(Grid* grid);
	void UpdateBuffers(Grid* grid);
	void UpdateDirtyBuffers(Grid* grid);

	void Clear() const;
	void Draw();

	inline Shader* GetShader() { return shader; }
	
private:
	Mesh* mesh;
	Shader* shader;
};
#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Window.h"
#include "Camera.h"

#include "../Components/Material.h"
#include "VertexArray.h"

struct Batch
{
	Material* material;
	VertexArray* vertexArray;
	Transform* transform;
};

class Renderer
{
public:
	Renderer(GLFWwindow* window);

	void SetViewport(int width, int height);

	//void BeginScene();
	//void EndScene();

	void NewBatch(Material* material, VertexArray* vertexArray, Transform* transform);

	void Render();

	Camera* GetCamera() { return &m_Camera; }

private:
	GLFWwindow* m_Window;
	Camera m_Camera;

	std::vector<Batch> m_Batches;
};
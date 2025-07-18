#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Window.h"
#include "Camera.h"

#include "../Core/Components/Material.h"
#include "../Core/Components/Transform.h"
#include "VertexArray.h"

#include <memory>

struct Batch
{
	std::weak_ptr<Material> material;
	std::weak_ptr<VertexArray> vertexArray;
	std::weak_ptr<Transform> transform;
};

class Renderer
{
public:
	Renderer(GLFWwindow* window);

	void SetViewport(int width, int height);

	//void BeginScene();
	//void EndScene();

	void NewBatch(std::weak_ptr<Material> material, std::weak_ptr<VertexArray> vertexArray, std::weak_ptr<Transform> transform);

	void RenderBatches();

	Camera* GetCamera() { return &m_Camera; }

private:
	GLFWwindow* m_Window;
	Camera m_Camera;

	std::vector<Batch> m_Batches;
};

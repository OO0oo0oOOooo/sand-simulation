#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	glm::mat4 GetModelMatrix() { return m_ModelMatrix; }
	glm::vec3 Position() { return glm::vec3(m_ModelMatrix[3]); }
	// glm::vec3 GetRotation();
	// glm::vec3 GetScale();

	void SetModelMatrix(glm::mat4 modelMatrix) { m_ModelMatrix = modelMatrix; }
	void SetPosition(glm::vec3 position) { m_ModelMatrix = glm::translate(m_ModelMatrix, position); }
	// void SetRotation(glm::vec3 rotation)
	// void SetScale(glm::vec3 scale) { m_ModelMatrix = glm::scale(m_ModelMatrix, scale); }

	// void TransformToLocalSpace(glm::vec3 position);
	// void TransformToWorldSpace(glm::vec3 position);

private:
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
};


/*
#include "Component.h"

class Transform : public Component {
public:
	Transform(GameObject* gameObject) : Component(gameObject) {}

	// ... transform properties and methods ...

	glm::mat4 GetModelMatrix() { return m_ModelMatrix; }

private:
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

};
*/
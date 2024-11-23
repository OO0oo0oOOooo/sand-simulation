#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Position
// View and Projection matrices

// FOV
// Aspect ratio
// Near and Far planes

// Camera class
class Camera
{
public:
	Camera();

	//void SetPosition(glm::vec3 position);
	//void SetRotation(glm::vec3 rotation);

	//void SetFOV(float fov);
	//void SetAspectRatio(float aspectRatio);
	//void SetNearPlane(float nearPlane);
	//void SetFarPlane(float farPlane);

	//glm::mat4 GetViewMatrix();
	//glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewProjectionMatrix();

	//glm::vec3 GetPosition();
	//glm::vec3 GetRotation();

	//float GetFOV();
	//float GetAspectRatio();
	//float GetNearPlane();
	//float GetFarPlane();

	//void Update();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	float m_FOV = 65.0f;
	float m_AspectRatio = 1.0f;
	float m_NearPlane = -1.0f;
	float m_FarPlane = 1.0f;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
};
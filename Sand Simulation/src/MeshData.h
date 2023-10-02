#include <glm/glm.hpp>

glm::vec3 vertexPositions[] = {
	glm::vec3(-0.0f, -0.0f, 0.0f),
	glm::vec3(-0.0f,  1.0f, 0.0f),
	glm::vec3( 1.0f, -0.0f, 0.0f),
	glm::vec3( 1.0f,  1.0f, 0.0f),
};

glm::vec4 vertexColors[] = {
	glm::vec4(0.9f, 0.8f, 0.2f, 1.0f),
	glm::vec4(0.9f, 0.2f, 0.8f, 1.0f),
	glm::vec4(0.2f, 0.9f, 0.8f, 1.0f),
	glm::vec4(0.5f, 0.2f, 0.5f, 1.0f),
};

unsigned int meshTriangles[] = {
	0, 1, 2,
	2, 1, 3,
};
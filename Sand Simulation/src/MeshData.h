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

glm::vec4 particleColors[] = {
	glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), // Air
	glm::vec4(0.9f, 0.8f, 0.2f, 1.0f), // Sand
	glm::vec4(0.2f, 0.9f, 0.8f, 1.0f), // Water
	glm::vec4(0.5f, 0.2f, 0.5f, 1.0f), // Rock
	glm::vec4(0.4f, 0.2f, 0.1f, 1.0f), // Wood
	glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), // Metal
	glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), // Gunpowder
	glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), // Fire
};
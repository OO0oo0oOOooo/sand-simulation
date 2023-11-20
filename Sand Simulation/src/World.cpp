#include "World.h"

void World::Render(Shader* shader)
{
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			chunks[glm::vec2(x, y)]->CreateMesh();
			chunks[glm::vec2(x, y)]->DrawMesh(shader);
		}
	}
}
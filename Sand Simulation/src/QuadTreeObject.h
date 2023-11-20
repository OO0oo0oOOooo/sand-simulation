#pragma once

#include "QuadTree.h"
#include "Mesh.h"

#include <iostream>

class QuadTreeObject
{
public:
	QuadTreeObject(int width, int depth);
	~QuadTreeObject();

	void UpdateNode(Node* node, float deltaTime);

	void Insert(glm::vec2 position, Cell cell);
	void Remove(glm::vec2 position);

	void DrawNode(Node* node);
	void Render(Shader* shader);
	void ClearMesh();

	QuadTree* quadTree;

	Mesh* mesh;
	Mesh* quadTreeMesh;
};
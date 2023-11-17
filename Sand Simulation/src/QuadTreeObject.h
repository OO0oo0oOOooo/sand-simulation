#pragma once

#include "QuadTree.h"
#include "Mesh.h"

class QuadTreeObject
{
public:
	QuadTreeObject(int width, int depth);
	~QuadTreeObject();

	void Update();

	void Insert(glm::vec2 position, Cell cell);
	void Remove(glm::vec2 position);

	void DrawNode(QuadTreeNode* node);
	void Render(Shader* shader);
	void ClearMesh();

	Mesh* mesh;
	Mesh* quadTreeMesh;

	QuadTree* quadTree;
};
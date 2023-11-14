#include "QuadTreeObject.h"

QuadTreeObject::QuadTreeObject(int width, int depth)
{
	mesh = new Mesh();
	quadTree = new QuadTree(0, 0, width, depth);
}

QuadTreeObject::~QuadTreeObject()
{
	delete mesh;
}

void QuadTreeObject::Insert(glm::vec2 position, Cell cell)
{
	quadTree->Insert(position, cell);
	DrawNode(quadTree->root);
}

void QuadTreeObject::DrawNode(QuadTreeNode* node)
{
	glm::vec4 color = { 1, 1, 1, 1 };

	if (node->isLeaf)
	{
		color = { 0.2f, 0.2f, 0.7f, 1.0f };
	}
	else
	{
		if(node->NW != nullptr)
			DrawNode(node->NW);

		if(node->NE != nullptr)
			DrawNode(node->NE);

		if(node->SW != nullptr)
			DrawNode(node->SW);
		
		if(node->SE != nullptr)
			DrawNode(node->SE);
	}

	for (int i = 0; i < 4; i++)
	{
		Vertex v;

		v.position = (glm::vec3(node->position, 0) + (vertexPositions[i]) * (float)node->size);
		v.color = color;

		mesh->vertices.push_back(v);
	}

	for (int i = 0; i < 6; i++)
	{
		mesh->indices.push_back(mesh->vertices.size() - 4 + meshTriangles[i]);
	}
}

void QuadTreeObject::Render(Shader* shader)
{
	mesh->UploadIBOData();
	mesh->UploadVBOData();
	mesh->Draw(shader);
}

void QuadTreeObject::ClearMesh()
{
	mesh->vertices.clear();
	mesh->indices.clear();
}
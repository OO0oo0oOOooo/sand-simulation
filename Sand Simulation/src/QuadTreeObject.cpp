#include "QuadTreeObject.h"

QuadTreeObject::QuadTreeObject(int width, int depth)
{
	mesh = new Mesh();
	quadTreeMesh = new Mesh();

	quadTree = new QuadTree(0, 0, width, depth);
}

QuadTreeObject::~QuadTreeObject()
{
	delete mesh;
	delete quadTreeMesh;
}

void QuadTreeObject::Update()
{
	// Run on every leaf node
}

void QuadTreeObject::Insert(glm::vec2 position, Cell cell)
{
	quadTree->Insert(position, cell);
	DrawNode(quadTree->root);
}

void QuadTreeObject::Remove(glm::vec2 position)
{
	quadTree->Remove(position);
	ClearMesh();
	DrawNode(quadTree->root);
}

void QuadTreeObject::DrawNode(QuadTreeNode* node)
{
	if (node->isLeaf)
	{
		for (int i = 0; i < 4; i++)
		{
			Vertex v;

			v.position = (glm::vec3(node->position, 0) + (vertexPositions[i]) * (float)node->size);
			v.color = node->cell.color;

			mesh->vertices.push_back(v);
		}

		for (int i = 0; i < 6; i++)
		{
			mesh->indices.push_back(mesh->vertices.size() - 4 + meshTriangles[i]);
		}
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
		v.color = {1,1,1,1};

		quadTreeMesh->vertices.push_back(v);
	}

	for (int i = 0; i < 6; i++)
	{
		quadTreeMesh->indices.push_back(quadTreeMesh->vertices.size() - 4 + meshTriangles[i]);
	}
}

void QuadTreeObject::Render(Shader* shader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	quadTreeMesh->UploadIBOData();
	quadTreeMesh->UploadVBOData();
	quadTreeMesh->Draw(shader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	mesh->UploadIBOData();
	mesh->UploadVBOData();
	mesh->Draw(shader);
}

void QuadTreeObject::ClearMesh()
{
	mesh->vertices.clear();
	mesh->indices.clear();

	quadTreeMesh->vertices.clear();
	quadTreeMesh->indices.clear();
}
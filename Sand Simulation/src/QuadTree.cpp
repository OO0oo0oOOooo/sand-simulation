#include "QuadTree.h"

#include <iostream>

Quadtree::Quadtree(int windowWidth, int windowHeight, int depth)
{
	//root = new QuadTreeNode(position, size);
	//root->Subdivide(depth);

	int width = windowWidth / 2;
	int height = windowHeight / 2;

	int size = width;// < height ? width : height;

	node1 = new QuadTreeNode(glm::vec2(0, 0), size);
	node2 = new QuadTreeNode(glm::vec2(size, 0), size);

	node1->Subdivide(depth);
	node2->Subdivide(depth);

	mesh = new Mesh();
}

Quadtree::~Quadtree()
{
	//delete root;
	delete node1;
	delete node2;
	
	delete mesh;
}

void Quadtree::DrawQuadTree()
{
	mesh->Clear();
	//DrawLeafNodeRecursive(root);

	DrawLeafNodeRecursive(node1);
	DrawLeafNodeRecursive(node2);
}

void Quadtree::RenderQuadTree(Shader* shader)
{
	mesh->UploadIBOData();
	mesh->UploadVBOData();
	mesh->Draw(shader);
}


QuadTreeNode::QuadTreeNode(glm::vec2 pos, int s)
{
	position = pos;
	size = s;

	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;

	isLeaf = false;
}

QuadTreeNode::~QuadTreeNode()
{
	if (NW != nullptr)
		delete NW;

	if (NE != nullptr)
		delete NE;

	if (SW != nullptr)
		delete SW;

	if (SE != nullptr)
		delete SE;
}

void QuadTreeNode::Subdivide(int depth)
{
	if (depth == 0)
	{
		isLeaf = true;
		return;
	}

	NW = new QuadTreeNode(glm::vec2(position.x,					position.y + size * 0.5f),	size / 2);
	NE = new QuadTreeNode(glm::vec2(position.x + size * 0.5f,	position.y + size * 0.5f),	size / 2);
	SW = new QuadTreeNode(glm::vec2(position.x,					position.y),				size / 2);
	SE = new QuadTreeNode(glm::vec2(position.x + size * 0.5f,	position.y),				size / 2);

	if (depth > 0)
	{
		NW->Subdivide(depth - 1);
		NE->Subdivide(depth - 1);
		SW->Subdivide(depth - 1);
		SE->Subdivide(depth - 1);
	}
}

//void QuadTreeNode::Insert(Cell cell)
//{
//}
//
//std::vector<Cell> QuadTreeNode::Query()
//{
//	return std::vector<Cell>();
//}
//
//std::vector<Cell> QuadTreeNode::QueryArea()
//{
//	return std::vector<Cell>();
//}

void Quadtree::DrawLeafNodeRecursive(QuadTreeNode* node)
{
	for (int i = 0; i < 4; i++)
	{
		Vertex v;

		v.position = (glm::vec3(node->position, 0) + (vertexPositions[i]) * (float)node->size);
		v.color = { 0.2f, 0.2f, 0.7f, 1.0f };

		mesh->vertices.push_back(v);
	}

	for (int i = 0; i < 6; i++)
	{
		mesh->indices.push_back(mesh->vertices.size() - 4 + meshTriangles[i]);
	}

	if (node->isLeaf) 
	{
		//std::cout << "Drawing node at position: " << node->position.x << ", " << node->position.y << " with size: " << node->size << std::endl;
	}
	else
	{
		DrawLeafNodeRecursive(node->NW);
		DrawLeafNodeRecursive(node->NE);
		DrawLeafNodeRecursive(node->SW);
		DrawLeafNodeRecursive(node->SE);
	}
}
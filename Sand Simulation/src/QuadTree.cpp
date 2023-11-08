#include "QuadTree.h"

Quadtree::Quadtree(int depth)
{
	root = new QuadTreeNode(glm::vec2(0, 0), 100);
	root->Subdivide(depth);
}

Quadtree::~Quadtree()
{
	delete root;
}

void Quadtree::DrawQuadTree()
{
	mesh.Clear();
	DrawNode(root, mesh);
}

void Quadtree::RenderQuadTree(Shader* shader)
{
	mesh.Draw(shader);
}




QuadTreeNode::QuadTreeNode(glm::vec2 position, int size)
{
	this->position = position;
	this->size = size;

	isLeaf = false;
}

QuadTreeNode::~QuadTreeNode()
{
	delete NW;
	delete NE;
	delete SW;
	delete SE;
}

void QuadTreeNode::Subdivide(int depth)
{
	if (depth == 0)
	{
		isLeaf = true;
		return;
	}

	NW = new QuadTreeNode(glm::vec2(position.x - size * 0.25f, position.y + size * 0.25f), size / 2);
	NE = new QuadTreeNode(glm::vec2(position.x + size * 0.25f, position.y + size * 0.25f), size / 2);
	SW = new QuadTreeNode(glm::vec2(position.x - size * 0.25f, position.y - size * 0.25f), size / 2);
	SE = new QuadTreeNode(glm::vec2(position.x + size * 0.25f, position.y - size * 0.25f), size / 2);

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

void DrawNode(QuadTreeNode* node, Mesh& mesh) {
	if (node->isLeaf) {
		//std::cout << "Drawing node at position: " << node->position.x << ", " << node->position.y << " with size: " << node->size << std::endl;

		for (int i = 0; i < 4; i++)
		{
			Vertex v;

			v.position = (glm::vec3(node->position, 0) + vertexPositions[i]) * (float)node->size;
			v.color = {0, 0, 0, 1};

			mesh.vertices.push_back(v);
		}

		for (int i = 0; i < 6; i++)
		{
			mesh.indices.push_back(mesh.vertices.size() - 4 + meshTriangles[i]);
		}

	}
	else {
		DrawNode(node->NW, mesh);
		DrawNode(node->NE, mesh);
		DrawNode(node->SW, mesh);
		DrawNode(node->SE, mesh);
	}
}
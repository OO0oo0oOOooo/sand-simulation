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
	DrawNode(root);
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

void DrawNode(QuadTreeNode* node) {
	if (node->isLeaf) {
		// Figure out how to send this data to the mesh
		// DrawSquare(node->position, node->size);

		//std::cout << "Drawing node at position: " << node->position.x << ", " << node->position.y << " with size: " << node->size << std::endl;
	}
	else {
		DrawNode(node->NW);
		DrawNode(node->NE);
		DrawNode(node->SW);
		DrawNode(node->SE);
	}
}
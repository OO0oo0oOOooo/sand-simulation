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

void Quadtree::Insert(Cell cell)
{
}

std::vector<Cell> Quadtree::Query()
{
	return std::vector<Cell>();
}





QuadTreeNode::QuadTreeNode(glm::vec2 position, int size)
{
	this->position = position;
	this->size = size;
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
#include "QuadTree.h"

#include <iostream>

QuadTree::QuadTree(int x, int y, int size, int depth)
{
	root = new QuadTreeNode(glm::vec2(x, y), size);
	//root->Subdivide(depth);
}

QuadTree::~QuadTree()
{
	delete root;
}

void QuadTree::Insert(glm::vec2 position, Cell cell)
{
	root->Subdivide(position, cell, 6);
}

void QuadTree::Remove(glm::vec2 position)
{
	root->Collapse(position, 6);
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

int	GetIndexFromPosition(glm::vec2 position, QuadTreeNode* node)
{
		int index = -1;

		if (position.x < node->position.x + node->size * 0.5f)
		{
			if (position.y < node->position.y + node->size * 0.5f)
			{
				index = 2;
			}
			else
			{
				index = 0;
			}
		}
		else
		{
			if (position.y < node->position.y + node->size * 0.5f)
			{
				index = 3;
			}
			else
			{
				index = 1;
			}
		}

	return index;

}

void QuadTreeNode::Subdivide(glm::vec2 position, Cell cell, int depth)
{
	if (depth == 0)
	{
		this->cell = cell;
		isLeaf = true;
		return;
	}

	int index = GetIndexFromPosition(position, this);

	// If the child doesn't exist, create it
	switch (index)
	{
	case 0:
		NW = new QuadTreeNode(glm::vec2(this->position.x,				this->position.y + size * 0.5f), size / 2);
		NW->Subdivide(position, cell, depth - 1);
		break;
	case 1:
		NE = new QuadTreeNode(glm::vec2(this->position.x + size * 0.5f, this->position.y + size * 0.5f), size / 2);
		NE->Subdivide(position, cell, depth - 1);
		break;
	case 2:
		SW = new QuadTreeNode(glm::vec2(this->position.x,				this->position.y), size / 2);
		SW->Subdivide(position, cell, depth - 1);
		break;
	case 3:
		SE = new QuadTreeNode(glm::vec2(this->position.x + size * 0.5f, this->position.y), size / 2);
		SE->Subdivide(position, cell, depth - 1);
		break;
	}
}

void QuadTreeNode::Collapse(glm::vec2 position, int depth)
{
	if (depth < 0)
	{
		return;
	}

	int index = GetIndexFromPosition(position, this);

	if(!isLeaf)
	{ 
		switch (index)
		{
		case 0:
			NW->Collapse(position, depth - 1);
			break;
		case 1:
			NE->Collapse(position, depth - 1);
			break;
		case 2:
			SW->Collapse(position, depth - 1);
			break;
		case 3:
			SE->Collapse(position, depth - 1);
			break;
		}
	}
	else
	{
		switch (index)
		{
		case 0:
			delete NW;
			NW = nullptr;
			break;
		case 1:
			delete NE;
			NE = nullptr;
			break;
		case 2:
			delete SW;
			SW = nullptr;
			break;
		case 3:
			delete SE;
			SE = nullptr;
			break;
		}
	}
	
}

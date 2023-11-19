#include "QuadTree.h"

#include <iostream>

QuadTree::QuadTree(int x, int y, int size, int depth)
{
	root = new QuadTreeNode(glm::vec2(x, y), size);
	root->isRoot = true;
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

int	GetIndexFromPosition(glm::vec2 position, QuadTreeNode* node)
{
	int index = -1;
	if (node == nullptr) return index;

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

QuadTreeNode* FindLeafNode(glm::vec2 position, QuadTreeNode* root)
{
	QuadTreeNode* node = root;

	while (!node->isLeaf)
	{
		int index = GetIndexFromPosition(position, node);

		switch (index)
		{
		case 0:
			if (node->NW != nullptr)
				node = node->NW;
			break;
		case 1:
			if (node->NE != nullptr)
				node = node->NE;
			break;
		case 2:
			if (node->SW != nullptr)
				node = node->SW;
			break;
		case 3:
			if (node->SE != nullptr)
				node = node->SE;
			break;
		default:
			return nullptr;
		}
	}

	return node;
}

void QuadTree::Remove(glm::vec2 position)
{
	QuadTreeNode* node = FindLeafNode(position, root);
	if (node == nullptr) return;

	if		(node->parent->NW == node) { delete node->parent->NW; node->parent->NW = nullptr; }
	else if (node->parent->NE == node) { delete node->parent->NE; node->parent->NE = nullptr; }
	else if (node->parent->SW == node) { delete node->parent->SW; node->parent->SW = nullptr; }
	else if (node->parent->SE == node) { delete node->parent->SE; node->parent->SE = nullptr; }

	node->parent->Collapse();
	//root->Remove(position);
}

QuadTreeNode::QuadTreeNode(glm::vec2 pos, int s)
{
	position = pos;
	size = s;

	parent = nullptr;
	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;

	isLeaf = false;
	isRoot = false;
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
		if(NW == nullptr)
			NW = new QuadTreeNode(glm::vec2(this->position.x,				this->position.y + size * 0.5f), size / 2);
		NW->Subdivide(position, cell, depth - 1);
		NW->parent = this;
		break;
	case 1:
		if(NE == nullptr)
			NE = new QuadTreeNode(glm::vec2(this->position.x + size * 0.5f, this->position.y + size * 0.5f), size / 2);
		NE->Subdivide(position, cell, depth - 1);
		NE->parent = this;
		break;
	case 2:
		if(SW == nullptr)
			SW = new QuadTreeNode(glm::vec2(this->position.x, this->position.y), size / 2);
		SW->Subdivide(position, cell, depth - 1);
		SW->parent = this;
		break;
	case 3:
		if(SE == nullptr)
			SE = new QuadTreeNode(glm::vec2(this->position.x + size * 0.5f, this->position.y), size / 2);
		SE->Subdivide(position, cell, depth - 1);
		SE->parent = this;
		break;
	}
}



void QuadTreeNode::Remove(glm::vec2 position)
{
	QuadTreeNode* node = FindLeafNode(position, this);

	if		(parent->NW == node) { delete parent->NW; parent->NW = nullptr; }
	else if (parent->NE == node) { delete parent->NE; parent->NE = nullptr; }
	else if (parent->SW == node) { delete parent->SW; parent->SW = nullptr; }
	else if (parent->SE == node) { delete parent->SE; parent->SE = nullptr; }

	parent->Collapse();

	/*if(this == nullptr)
		return;

	int index = GetIndexFromPosition(position, this);

	if (!isLeaf)
	{
		switch (index)
		{
		case 0:
			if (NW != nullptr)
				NW->Remove(position);
			break;
		case 1:
			if (NE != nullptr)
				NE->Remove(position);
			break;
		case 2:
			if (SW != nullptr)
				SW->Remove(position);
			break;
		case 3:
			if (SE != nullptr)
				SE->Remove(position);
			break;
		default:
			return;
		}
	}
	else
	{
		switch (index)
		{
			case 0:
				delete parent->NW;
				parent->NW = nullptr;
				break;
			case 1:
				delete parent->NE;
				parent->NE = nullptr;
				break;
			case 2:
				delete parent->SW;
				parent->SW = nullptr;
				break;
			case 3:
				delete parent->SE;
				parent->SE = nullptr;
				break;
			default:
				return;
		}
	}*/

	//if (parent != nullptr)
	//parent->Collapse();
}

void QuadTreeNode::Collapse()
{
	if (this == nullptr || this->isRoot)
		return;

	if (NW == nullptr && NE == nullptr && SW == nullptr && SE == nullptr)
	{
		if		(parent->NW == this) { delete parent->NW; parent->NW = nullptr; }
		else if (parent->NE == this) { delete parent->NE; parent->NE = nullptr; }
		else if (parent->SW == this) { delete parent->SW; parent->SW = nullptr; }
		else if (parent->SE == this) { delete parent->SE; parent->SE = nullptr; }

		//if (parent != nullptr)
		parent->Collapse();
	}
}

	//int index = GetIndexFromPosition(position, this);

	//if (depth == 1)
	//{
	//	switch (index)
	//	{
	//	case 0:
	//		delete NW;
	//		NW = nullptr;
	//		break;
	//	case 1:
	//		delete NE;
	//		NE = nullptr;
	//		break;
	//	case 2:
	//		delete SW;
	//		SW = nullptr;
	//		break;
	//	case 3:
	//		delete SE;
	//		SE = nullptr;
	//		break;
	//	}
	//	return;
	//}
	//else if(depth > 0)
	//{
	//	switch (index)
	//	{
	//	case 0:
	//		if(NW != nullptr)
	//			NW->Collapse(position, depth - 1);
	//		break;
	//	case 1:
	//		if(NE != nullptr)
	//			NE->Collapse(position, depth - 1);
	//		break;
	//	case 2:
	//		if(SW != nullptr)
	//			SW->Collapse(position, depth - 1);
	//		break;
	//	case 3:
	//		if(SE != nullptr)
	//			SE->Collapse(position, depth - 1);
	//		break;
	//	}
	//}
//}

#include "QuadTree.h"

#include <iostream>

QuadTree::QuadTree(int x, int y, int size, int depth)
	: depth(depth)
{
	root = new Node(glm::vec2(x, y), size);
	root->isRoot = true;
}

QuadTree::~QuadTree()
{
	delete root;
}

void QuadTree::Insert(glm::vec2 position, Cell cell)
{
	root->Subdivide(position, cell, depth);
}

int	GetIndexFromPosition(glm::vec2 position, Node* node)
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

Node* GetNodeFromPosition(glm::vec2 position, Node* node)
{
	if (node == nullptr) return nullptr;
	if (node->NW == nullptr && node->NE == nullptr && node->SW == nullptr && node->SE == nullptr) return nullptr;

	if (position.x < node->position.x + node->size * 0.5f)
	{
		if (position.y < node->position.y + node->size * 0.5f)
		{
			if(node->SW != nullptr)
				return node->SW;
		}
		else
		{
			if(node->NW != nullptr)
				return node->NW;
		}
	}
	else
	{
		if (position.y < node->position.y + node->size * 0.5f)
		{
			if(node->SE != nullptr)
				return node->SE;
		}
		else
		{
			if(node->NE != nullptr)
				return node->NE;
		}
	}

	return nullptr;
}

Node* FindLeafNode(glm::vec2 position, Node* root)
{
	Node* node = root;

	while (!node->isLeaf)
	{
		node = GetNodeFromPosition(position, node);
		if(node == nullptr) return nullptr;
	}

	return node;
}

void QuadTree::Remove(glm::vec2 position)
{
	Node* node = FindLeafNode(position, root);
	if (node == nullptr) return;

	Node* parent = node->parent;
	if (parent == nullptr) return;

	if		(parent->NW == node) { parent->NW = nullptr; }
	else if (parent->NE == node) { parent->NE = nullptr; }
	else if (parent->SW == node) { parent->SW = nullptr; }
	else if (parent->SE == node) { parent->SE = nullptr; }

	delete node;

	parent->Collapse();
}

Node::Node(glm::vec2 pos, int s)
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

Node::~Node()
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

void Node::Subdivide(glm::vec2 position, Cell cell, int depth)
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
			NW = new Node(glm::vec2(this->position.x,				this->position.y + size * 0.5f), size / 2);
		NW->Subdivide(position, cell, depth - 1);
		NW->parent = this;
		break;
	case 1:
		if(NE == nullptr)
			NE = new Node(glm::vec2(this->position.x + size * 0.5f, this->position.y + size * 0.5f), size / 2);
		NE->Subdivide(position, cell, depth - 1);
		NE->parent = this;
		break;
	case 2:
		if(SW == nullptr)
			SW = new Node(glm::vec2(this->position.x, this->position.y), size / 2);
		SW->Subdivide(position, cell, depth - 1);
		SW->parent = this;
		break;
	case 3:
		if(SE == nullptr)
			SE = new Node(glm::vec2(this->position.x + size * 0.5f, this->position.y), size / 2);
		SE->Subdivide(position, cell, depth - 1);
		SE->parent = this;
		break;
	}
}

void Node::Collapse()
{
	if (this == nullptr || this->isRoot)
		return;

	Node* parent = this->parent;

	if (NW == nullptr && NE == nullptr && SW == nullptr && SE == nullptr)
	{
		if		(parent->NW == this) { delete parent->NW; parent->NW = nullptr; }
		else if (parent->NE == this) { delete parent->NE; parent->NE = nullptr; }
		else if (parent->SW == this) { delete parent->SW; parent->SW = nullptr; }
		else if (parent->SE == this) { delete parent->SE; parent->SE = nullptr; }

		if (parent != nullptr)
			parent->Collapse();
	}
}
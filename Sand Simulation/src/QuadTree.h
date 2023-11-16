#pragma once

#include "Cell.h"

// TODO:
// Get Detail where required.
// Exclude cells that are occupied but shouldnt be checked for updates
// 
// [ ] Add/remove function
// [ ] check nehbouring cells for updates
// [ ] Collapse tree if all cells are the same


class QuadTreeNode
{
public:
    QuadTreeNode(glm::vec2 position, int size);
    ~QuadTreeNode();

    //std::vector<Cell> Query(x, y);

    void Subdivide(glm::vec2 position, Cell cell, int depth);

    glm::vec2 position;
    int size;
    Cell cell;

    QuadTreeNode* NW;
    QuadTreeNode* NE;
    QuadTreeNode* SW;
    QuadTreeNode* SE;

    bool isLeaf;
};

class QuadTree {
public:
    QuadTree(int x, int y, int size, int depth);
    ~QuadTree();

    void Insert(glm::vec2 position, Cell cell);

    QuadTreeNode* root;
};
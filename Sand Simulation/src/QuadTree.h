#pragma once

#include "Cell.h"

// TODO:
// Get Detail where required.
// Exclude cells that are occupied but shouldnt be checked for updates
// 
// [ ] Think of how i want to query the quadtree
//      If this node is a leaf, return area into a larger array?
//      Loop through this subsection of the grid and do updates from here?
// 
// [ ] Think of how i want to subdivide the quadtree
//      If node is entirely occupied, do not subdivide.
//      If node is not entirely occupied, subdivide for more precision.
//
// [ ] Change IsLeaf to be if the node has no children

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
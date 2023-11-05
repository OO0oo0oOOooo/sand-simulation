#pragma once

#include "Cell.h"

#include <vector>

// Get Detail where required.
// Exclude cells that are occupied but shouldnt be checked for updates

class QuadTreeNode
{
public:
    QuadTreeNode(glm::vec2 position, int size);
    ~QuadTreeNode();

    //void Insert(Cell cell);
    //std::vector<Cell> Query(); // If this node is a leaf, return data? // If this node is in Occupied return data?
    //std::vector<Cell> QueryArea(); // parameters to define query area

    void Subdivide(int depth); // If node is not entirely occupied, subdivide for more precision. If node is entirely occupied or entirly unoccupied, do not subdivide.

private:
    glm::vec2 position;
    int size;

    QuadTreeNode* NW;
    QuadTreeNode* NE;
    QuadTreeNode* SW;
    QuadTreeNode* SE;

    Cell data;

    bool isLeaf;
    bool isOccupied;
};

class Quadtree {
public:
    Quadtree(int depth);
    ~Quadtree();

    void Insert(Cell cell);
    std::vector<Cell> Query(); // If this node is a leaf, return data? // If this node is occupied return data?

private:
    QuadTreeNode* root;
    int maxDepth;
};




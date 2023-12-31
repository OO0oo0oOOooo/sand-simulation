#pragma once

#include "Cell.h"

// TODO:
// Get Detail where required.
// Exclude cells that are occupied but shouldnt be checked for updates
// 
// Functionality:
// [ ] check nehbouring cells
// 
// Optimizations:
// [ ] Collapse tree if all cells are the same


class Node
{
public:
    Node(glm::vec2 position, int size);
    ~Node();

    //std::vector<Cell> Query(x, y);

    void Subdivide(glm::vec2 position, Cell cell, int depth);
    void Collapse();

    glm::vec2 position;
    int size;
    Cell cell;

    Node* parent;
    Node* NW;
    Node* NE;
    Node* SW;
    Node* SE;

    bool isLeaf;
    bool isRoot;
};

class QuadTree {
public:
    QuadTree(int x, int y, int size, int depth);
    ~QuadTree();

    void Insert(glm::vec2 position, Cell cell);
    void Remove(glm::vec2 position);

    Node* root;

private:
    int depth;
};
#pragma once

#include "Mesh.h"

// TODO:
// Get Detail where required.
// Exclude cells that are occupied but shouldnt be checked for updates
// 
// [ ] Think of how i want to build/send the leaf node mesh data to the mesh
//      // 
// 
// [ ] Think of how i want to query the quadtree
//      If this node is a leaf, return area into a larger array?
//      Loop through this subsection of the grid and do updates from here?
// 
// [ ] Think of how i want to subdivide the quadtree
//      If node is entirely occupied or entirly unoccupied, do not subdivide.
//      If node is not entirely occupied, subdivide for more precision. 

class QuadTreeNode
{
public:
    QuadTreeNode(glm::vec2 position, int size);
    ~QuadTreeNode();

    //void Insert(Cell cell);
    //std::vector<Cell> Query(); 
    //std::vector<Cell> QueryArea(); // parameters to define query area

    void Subdivide(int depth);

    glm::vec2 position;
    int size;

    QuadTreeNode* NW = nullptr;
    QuadTreeNode* NE = nullptr;
    QuadTreeNode* SW = nullptr;
    QuadTreeNode* SE = nullptr;

    bool isLeaf;
};

class Quadtree {
public:
    Quadtree(int depth);
    ~Quadtree();

    void DrawQuadTree();

    QuadTreeNode* root;
    Mesh mesh;
};

void DrawNode(QuadTreeNode* node);




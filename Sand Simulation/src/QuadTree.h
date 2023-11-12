#pragma once

#include "Mesh.h"
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

    QuadTreeNode* NW;
    QuadTreeNode* NE;
    QuadTreeNode* SW;
    QuadTreeNode* SE;

    bool isLeaf;
};

class Quadtree {
public:
    Quadtree(int windowWidth, int windowHeight, int depth);
    ~Quadtree();

    void DrawLeafNodeRecursive(QuadTreeNode* node);

    void DrawQuadTree();
    void RenderQuadTree(Shader* shader);

    //QuadTreeNode* root;
    QuadTreeNode* node1;
    QuadTreeNode* node2;
    QuadTreeNode* node3;
    QuadTreeNode* node4;

    QuadTreeNode* node5;
    QuadTreeNode* node6;
    QuadTreeNode* node7;
    QuadTreeNode* node8;

    Mesh* mesh;
};






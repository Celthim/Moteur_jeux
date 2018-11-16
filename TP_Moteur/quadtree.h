#ifndef QUADTREE_H
#define QUADTREE_H

#include "vertexdata.h"

class QuadTree
{

public:
    QuadTree();
    QuadTree* compute(VertexData* vertices,int sizex, int sizey);
    void init(VertexData* vertices, int sizex, int sizey);

    VertexData value[4];
    QuadTree* f1;
    QuadTree* f2;
    QuadTree* f3;
    QuadTree* f4;
};

#endif // QUADTREE_H

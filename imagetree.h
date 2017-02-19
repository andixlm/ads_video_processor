#ifndef IMAGETREE_H
#define IMAGETREE_H

#include "polygon.h"

class Node
{
    Polygon mPolygon;
    Node* mLeftChild;
    Node* mRightChild;
};

class ImageTree
{
public:
    ImageTree(Node* head = nullptr);

    void add(Polygon polygon);

private:
    Node* mHead;
};

#endif // IMAGETREE_H

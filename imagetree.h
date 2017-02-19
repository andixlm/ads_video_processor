#ifndef IMAGETREE_H
#define IMAGETREE_H

#include "polygon.h"

class ImageTree;

class Node
{
    friend ImageTree;

public:
    Node(Polygon polygon = Polygon(), Node* parent = nullptr,
         Node* leftChild = nullptr, Node* rightChild = nullptr);

private:
    Polygon mPolygon;

    Node* mParent;
    Node* mLeftChild;
    Node* mRightChild;
};

class ImageTree
{
public:
    ImageTree(Node* head = nullptr);

    void add(Polygon polygon);
    void clear() { _clear(mHead); mHead = nullptr; }

    Node* getHead();

private:
    Node* mHead;

    void _clear(Node* node);
};

#endif // IMAGETREE_H

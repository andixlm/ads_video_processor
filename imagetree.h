#ifndef IMAGETREE_H
#define IMAGETREE_H

#include "polygon.h"

class ImageTree;

class Node
{
    friend ImageTree;

public:
    Node(Polygon polygon, Node* parent = nullptr,
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
    explicit ImageTree(Node* head = nullptr);
    ~ImageTree();

    void insert(Polygon polygon) { mHead = _insert(polygon, nullptr, mHead); }
    void clear() { _clear(mHead); mHead = nullptr; }

    Node* getHead();

private:
    Node* mHead;

    Node* _insert(Polygon polygon, Node* parent = nullptr, Node* node = nullptr);
    void _clear(Node* node);

    bool isLeftChild(Polygon& newPolygon, Polygon& currentPolygon);
};

#endif // IMAGETREE_H

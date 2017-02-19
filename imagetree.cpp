#include "imagetree.h"

Node::Node(Polygon polygon, Node* parent, Node* leftChild, Node* rightChild) :
    mPolygon(polygon), mParent(parent), mLeftChild(leftChild), mRightChild(rightChild)
{

}

ImageTree::ImageTree(Node* head) :
    mHead(head)
{

}

void ImageTree::clear()
{
    _clear(mHead);
    mHead = nullptr;
}

void ImageTree::_clear(Node* node)
{
    if (!node)
        return;

    _clear(node->mLeftChild);
    _clear(node->mRightChild);

    delete node;
}

Node* ImageTree::getHead()
{
    return mHead;
}

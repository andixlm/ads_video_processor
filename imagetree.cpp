#include "exception.h"
#include "imagetree.h"

Node::Node(Polygon polygon, Node* parent, Node* leftChild, Node* rightChild) :
    mPolygon(polygon), mParent(parent), mLeftChild(leftChild), mRightChild(rightChild)
{

}

ImageTree::ImageTree(Node* head) :
    mHead(head)
{

}

Node* ImageTree::_insert(Polygon polygon, Node* parent, Node* node)
{
    if (!node) {
        Node* temp = new Node(polygon, parent);

        if (!temp)
            throw Exception::OutOfMemory();

        return temp;
    }

    if (isLeftChild(polygon, node->mPolygon))
        node->mLeftChild = _insert(polygon, node, node->mLeftChild);
    else
        node->mRightChild = _insert(polygon, node, node->mRightChild);

    return node;
}

void ImageTree::_clear(Node* node)
{
    if (!node)
        return;

    _clear(node->mLeftChild);
    _clear(node->mRightChild);

    delete node;
}

// TODO: Gotta implement.
bool ImageTree::isLeftChild(Polygon& newPolygon, Polygon& currentPolygon)
{
    return true;
}

Node* ImageTree::getHead()
{
    return mHead;
}

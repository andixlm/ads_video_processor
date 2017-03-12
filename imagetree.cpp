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

ImageTree::~ImageTree()
{
    _clear(mHead);
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

bool ImageTree::isLeftChild(Polygon& newPolygon, Polygon& currentPolygon)
{
    int width = currentPolygon.getBottomRight().x() - currentPolygon.getTopLeft().x();
    int height = currentPolygon.getBottomRight().y() - currentPolygon.getTopLeft().y();

    int middleWidth = (currentPolygon.getBottomRight().x() + currentPolygon.getTopLeft().x()) / 2;
    int middleHeight = (currentPolygon.getBottomRight().y() + currentPolygon.getTopLeft().y()) / 2;

    if (width > height)
      if (newPolygon.getTopLeft().x() < middleWidth)
        return true;
      else
        return false;
    else
      if (newPolygon.getTopLeft().y() < middleHeight)
        return true;
      else
        return false;
}

Node* ImageTree::getHead()
{
    return mHead;
}

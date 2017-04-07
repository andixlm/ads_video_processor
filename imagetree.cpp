#include "exception.h"
#include "imagetree.h"
#include "tools.h"

Node::Node(Polygon polygon, Node* parent, Node* leftChild, Node* rightChild)
{
    mPolygon = polygon;
    mParent = parent;
    mLeftChild = leftChild;
    mRightChild = rightChild;
}

ImageTree::ImageTree(Node* head)
{
    mHead = head;
    mPolygonsNumber = 0;
}

ImageTree::~ImageTree()
{
    _clear(mHead);
}

Node* ImageTree::getHead()
{
    return mHead;
}

void ImageTree::_getPolygonsNumber(Node* node)
{
    if (!node)
        return;

    _getPolygonsNumber(node->mLeftChild);
    _getPolygonsNumber(node->mRightChild);

    if (isLeaf(node))
        ++mPolygonsNumber;
}

QImage ImageTree::toImageGrid()
{
    QImage image = Tools::getBlankImage(mHead->mPolygon.getSize());
    _toImageGrid(image, mHead);

    return image;
}

void ImageTree::_toImageGrid(QImage& image, Node* node)
{
    if (!node)
        return;

    _toImageGrid(image, node->mLeftChild);
    _toImageGrid(image, node->mRightChild);

    if (isLeaf(node))
        Tools::drawPolygon(image, node->mPolygon);
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

bool ImageTree::isLeaf(Node* node)
{
    if (!node->mLeftChild && !node->mRightChild)
        return true;

    return false;
}

bool ImageTree::isLeftChild(Polygon& newPolygon, Polygon& currentPolygon)
{
    if (currentPolygon.getWidth() >= currentPolygon.getHeight())
      if (newPolygon.getTopLeft().x() <= currentPolygon.getMiddleWidth())
        return true;
      else
        return false;
    else
      if (newPolygon.getTopLeft().y() <= currentPolygon.getMiddleHeight())
        return true;
      else
        return false;
}

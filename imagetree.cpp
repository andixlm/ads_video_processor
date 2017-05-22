#include <QQueue>

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

QImage ImageTree::toImage()
{
    QImage image = Tools::getBlankImage(mHead->mPolygon.getSize());
    _toImage(image, mHead);

    return image;
}

void ImageTree::_toImage(QImage& image, Node* node)
{
    if (!node)
        return;

    _toImage(image, node->mLeftChild);
    _toImage(image, node->mRightChild);

    if (isLeaf(node))
        Tools::fillPolygon(image, node->mPolygon);
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
        Tools::drawPolygon(image, node->mPolygon, Qt::black);
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

Polygon* ImageTree::getPolygonByPoint(double x, double y)
{
    if (isEmpty())
        return nullptr;

    QQueue<Node*> nodes;
    nodes.enqueue(getHead());

    while (!nodes.empty()) {
        Node* currentNode = nodes.dequeue();

        if (currentNode->mLeftChild != nullptr || currentNode->mRightChild != nullptr) {
            nodes.enqueue(currentNode->mLeftChild);
            nodes.enqueue(currentNode->mRightChild);
        } else {
            if (currentNode->mPolygon.hasPoint(x, y))
                return &currentNode->mPolygon;
        }
    }

    return nullptr;
}

Polygon* ImageTree::getPolygonByPoint(QPoint point)
{
    if (isEmpty())
        return nullptr;

    QQueue<Node*> nodes;
    nodes.enqueue(getHead());

    while (!nodes.empty()) {
        Node* currentNode = nodes.dequeue();

        if (currentNode->mLeftChild != nullptr || currentNode->mRightChild != nullptr) {
            nodes.enqueue(currentNode->mLeftChild);
            nodes.enqueue(currentNode->mRightChild);
        } else {
            if (currentNode->mPolygon.hasPoint(point))
                return &currentNode->mPolygon;
        }
    }

    return nullptr;
}

QVector<Polygon*> ImageTree::getPolygonsBySize(int size)
{
    QQueue<Node*> nodes;
    nodes.enqueue(getHead());

    QVector<Polygon*> polygons;
    while (!nodes.empty()) {
        Node* currentNode = nodes.dequeue();

        if (currentNode->mLeftChild != nullptr || currentNode->mRightChild != nullptr) {
            nodes.enqueue(currentNode->mLeftChild);
            nodes.enqueue(currentNode->mRightChild);
        } else {
            if (currentNode->mPolygon.isSize(size))
                polygons.append(&currentNode->mPolygon);
        }
    }

    return polygons;
}

QVector<Polygon*> ImageTree::getAdjacentPolygonsBySize(Polygon* polygon, int size)
{
    QQueue<Polygon*> adjacentPolygons;

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() + 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getBottomRight().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() - 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getBottomRight().y() - 1)));

    QVector<Polygon*> adjacentSizedPolygons;
    while (!adjacentPolygons.empty()) {
        Polygon* currentPolygon = adjacentPolygons.dequeue();

        if (Polygon::isSizeThreshold(*currentPolygon, size))
            adjacentSizedPolygons.append(currentPolygon);
    }

    return adjacentSizedPolygons;
}

void ImageTree::getAllAdjacentPolygonsBySize(Polygon* polygon, int size, QVector<Polygon*>* polygons)
{
    if (polygon != nullptr && polygon->isSize(size) && !polygons->contains(polygon))
        polygons->append(polygon);
    else
        return;

    Polygon* upperLeft = getPolygonByPoint(static_cast<double>(polygon->getTopLeft().x()) - 0.5,
                                           static_cast<double>(polygon->getTopLeft().y()) - 0.5);

    Polygon* upper = getPolygonByPoint(static_cast<double>(polygon->getTopLeft().x()) + 0.5,
                                       static_cast<double>(polygon->getTopLeft().y()) - 0.5);

    Polygon* upperRight = getPolygonByPoint(static_cast<double>(polygon->getBottomRight().x()) + 0.5,
                                            static_cast<double>(polygon->getTopLeft().y()) - 0.5);

    Polygon* right = getPolygonByPoint(static_cast<double>(polygon->getBottomRight().x()) + 0.5,
                                       static_cast<double>(polygon->getBottomRight().y()) - 0.5);

    Polygon* lowerRight = getPolygonByPoint(static_cast<double>(polygon->getBottomRight().x()) + 0.5,
                                            static_cast<double>(polygon->getBottomRight().y()) + 0.5);

    Polygon* lower = getPolygonByPoint(static_cast<double>(polygon->getBottomRight().x()) - 0.5,
                                       static_cast<double>(polygon->getBottomRight().y()) + 0.5);

    Polygon* lowerLeft = getPolygonByPoint(static_cast<double>(polygon->getTopLeft().x()) - 0.5,
                                           static_cast<double>(polygon->getBottomRight().y()) + 0.5);

    Polygon* left = getPolygonByPoint(static_cast<double>(polygon->getTopLeft().x()) - 0.5,
                                      static_cast<double>(polygon->getBottomRight().y()) - 0.5);


    getAllAdjacentPolygonsBySize(upperLeft, size, polygons);
    getAllAdjacentPolygonsBySize(upper, size, polygons);
    getAllAdjacentPolygonsBySize(upperRight, size, polygons);
    getAllAdjacentPolygonsBySize(right, size, polygons);
    getAllAdjacentPolygonsBySize(lowerRight, size, polygons);
    getAllAdjacentPolygonsBySize(lower, size, polygons);
    getAllAdjacentPolygonsBySize(lowerLeft, size, polygons);
    getAllAdjacentPolygonsBySize(left, size, polygons);
}

QVector<Polygon*> ImageTree::getAdjacentPolygonsByBrightness(Polygon* polygon, int brightness, int threshold)
{
    QQueue<Polygon*> adjacentPolygons;

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() + 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getTopLeft().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getBottomRight().y() - 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() + 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getBottomRight().x() - 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getBottomRight().y() + 1)));

    adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon->getTopLeft().x() - 1,
                                                      polygon->getBottomRight().y() - 1)));

    QVector<Polygon*> adjacentSameBrightPolygons;
    while (!adjacentPolygons.empty()) {
        Polygon* currentPolygon = adjacentPolygons.dequeue();

        if (qAbs(currentPolygon->getColor().getBrightness() - brightness) < threshold)
            adjacentSameBrightPolygons.append(currentPolygon);
    }

    return adjacentSameBrightPolygons;
}

void ImageTree::getAllAdjacentPolygonsByBrightness(Polygon* polygon, int brightness, int threshold, QVector<Polygon*>* polygons)
{
    int brightnessDifference = qAbs(polygon->getColor().getBrightness() - brightness);

    if (polygon != nullptr && brightnessDifference < threshold && !polygons->contains(polygon))
        polygons->append(polygon);
    else
        return;

    Polygon* upperLeft =    getPolygonByPoint(QPoint(polygon->getTopLeft().x()      - 1, polygon->getTopLeft().y()      - 1));
    Polygon* upper =        getPolygonByPoint(QPoint(polygon->getTopLeft().x()      + 1, polygon->getTopLeft().y()      - 1));
    Polygon* upperRight =   getPolygonByPoint(QPoint(polygon->getBottomRight().x()  + 1, polygon->getTopLeft().y()      - 1));
    Polygon* right =        getPolygonByPoint(QPoint(polygon->getBottomRight().x()  + 1, polygon->getBottomRight().y()  - 1));
    Polygon* lowerRight =   getPolygonByPoint(QPoint(polygon->getBottomRight().x()  + 1, polygon->getBottomRight().y()  + 1));
    Polygon* lower =        getPolygonByPoint(QPoint(polygon->getBottomRight().x()  - 1, polygon->getBottomRight().y()  + 1));
    Polygon* lowerLeft =    getPolygonByPoint(QPoint(polygon->getTopLeft().x()      - 1, polygon->getBottomRight().y()  + 1));
    Polygon* left =         getPolygonByPoint(QPoint(polygon->getTopLeft().x()      - 1, polygon->getBottomRight().y()  - 1));

    if (upperLeft)  getAllAdjacentPolygonsByBrightness(upperLeft,   brightness, threshold, polygons);
    if (upper)      getAllAdjacentPolygonsByBrightness(upper,       brightness, threshold, polygons);
    if (upperRight) getAllAdjacentPolygonsByBrightness(upperRight,  brightness, threshold, polygons);
    if (right)      getAllAdjacentPolygonsByBrightness(right,       brightness, threshold, polygons);
    if (lowerRight) getAllAdjacentPolygonsByBrightness(lowerRight,  brightness, threshold, polygons);
    if (lower)      getAllAdjacentPolygonsByBrightness(lower,       brightness, threshold, polygons);
    if (lowerLeft)  getAllAdjacentPolygonsByBrightness(lowerLeft,   brightness, threshold, polygons);
    if (left)       getAllAdjacentPolygonsByBrightness(left,        brightness, threshold, polygons);
}

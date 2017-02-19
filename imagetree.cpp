#include "imagetree.h"

ImageTree::ImageTree(Node* head) :
    mHead(head)
{

}

void ImageTree::clear()
{
    _clear(getHead());
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

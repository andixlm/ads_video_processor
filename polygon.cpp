#include "polygon.h"

Polygon::Polygon(QPoint topLeft, QPoint bottomRight, Rgb color) :
    mTopLeft(topLeft), mBottomRight(bottomRight), mColor(color)
{

}

Rgb Polygon::getColor()
{
    return mColor;
}

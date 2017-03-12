#include "polygon.h"

Polygon::Polygon(QImage& image, QPoint topLeft, QPoint bottomRight)
{
    mTopLeft = topLeft;
    mBottomRight = bottomRight;
    mColor = Rgb(image, topLeft, bottomRight);
}

Polygon::Polygon(QPoint topLeft, QPoint bottomRight, Rgb color)
{
    mTopLeft = topLeft;
    mBottomRight = bottomRight;
    mColor = color;
}

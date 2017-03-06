#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>

#include "rgb.h"

class Polygon
{
public:
    Polygon(QPoint topLeft = QPoint(), QPoint bottomRight = QPoint(),
            Rgb color = Rgb());

    QPoint getTopLeft() { return mTopLeft; }
    QPoint getBottomRight() { return mBottomRight; }
    Rgb getColor() { return mColor; }

private:
    QPoint mTopLeft;
    QPoint mBottomRight;
    Rgb mColor;
};

#endif // POLYGON_H

#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>
#include <QSize>

#include "rgb.h"

class Polygon
{
public:
    Polygon(QPoint topLeft = QPoint(), QPoint bottomRight = QPoint(),
            Rgb color = Rgb());

    QPoint getTopLeft() { return mTopLeft; }
    void setTopLeft(QPoint topLeft) { mTopLeft = topLeft; }
    QPoint getBottomRight() { return mBottomRight; }
    void setBottomRight(QPoint bottomRight) { mBottomRight = bottomRight; }

    int getWidth() { return getBottomRight().x() - getTopLeft().x(); }
    int getHeight() { return getBottomRight().y() - getTopLeft().y(); }
    QSize getSize() { return QSize(getWidth(), getHeight()); }

    Rgb getColor() { return mColor; }
    void setColor(Rgb color) { mColor = color; }

private:
    QPoint mTopLeft;
    QPoint mBottomRight;
    Rgb mColor;
};

#endif // POLYGON_H

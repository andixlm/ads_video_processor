#ifndef POLYGON_H
#define POLYGON_H

#include <QImage>
#include <QPoint>
#include <QSize>

#include "rgb.h"

class Polygon
{
public:
    Polygon(QPoint topLeft, QPoint bottomRight, Rgb color);
    Polygon(QImage& image, QPoint topLeft, QPoint bottomRight);

    QPoint getTopLeft() { return mTopLeft; }
    void setTopLeft(QPoint topLeft) { mTopLeft = topLeft; }
    QPoint getBottomRight() { return mBottomRight; }
    void setBottomRight(QPoint bottomRight) { mBottomRight = bottomRight; }

    int getWidth() { return getBottomRight().x() - getTopLeft().x(); }
    int getHeight() { return getBottomRight().y() - getTopLeft().y(); }
    int getMiddleWidth() { return (getBottomRight().x() + getTopLeft().x()) / 2; }
    int getMiddleHeight() { return (getBottomRight().y() + getTopLeft().y()) / 2; }
    QSize getSize() { return QSize(getWidth(), getHeight()); }

    Rgb getColor() { return mColor; }
    void setColor(Rgb color) { mColor = color; }

    static bool isSizeThreshold(Polygon polygon, int threshold);
    static bool isBrightnessThreshold(QImage& image, Polygon polygon, int threshold);

private:
    QPoint mTopLeft;
    QPoint mBottomRight;
    Rgb mColor;
};

#endif // POLYGON_H

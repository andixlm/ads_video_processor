#ifndef POLYGON_H
#define POLYGON_H

#include <QImage>
#include <QPoint>
#include <QSize>

#include "rgb.h"

class Polygon
{
public:
    Polygon(QImage& image, QPoint topLeft, QPoint bottomRight);
    Polygon(QPoint topLeft = QPoint(), QPoint bottomRight = QPoint(), Rgb color = Rgb());

    QPoint getTopLeft() { return mTopLeft; }
    void setTopLeft(QPoint topLeft) { mTopLeft = topLeft; }
    QPoint getBottomRight() { return mBottomRight; }
    void setBottomRight(QPoint bottomRight) { mBottomRight = bottomRight; }

    int getWidth() { return getBottomRight().x() - getTopLeft().x() + 1; }
    int getHeight() { return getBottomRight().y() - getTopLeft().y() + 1; }
    int getMiddleWidth() { return (getTopLeft().x() + getBottomRight().x()) / 2; }
    int getMiddleHeight() { return (getTopLeft().y() + getBottomRight().y()) / 2; }
    QSize getSize() { return QSize(getWidth(), getHeight()); }

    Rgb getColor() { return mColor; }
    void setColor(Rgb color) { mColor = color; }

    static bool isSizeThreshold(Polygon polygon, int threshold);
    static bool isBrightnessThreshold(QImage& image, Polygon& polygon, int threshold);

private:
    QPoint mTopLeft;
    QPoint mBottomRight;
    Rgb mColor;
};

#endif // POLYGON_H

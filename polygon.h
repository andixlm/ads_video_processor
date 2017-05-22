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

    bool operator==(Polygon& rhs);
    bool operator!=(Polygon& rhs);

    inline QPoint getTopLeft() { return mTopLeft; }
    inline void setTopLeft(QPoint topLeft) { mTopLeft = topLeft; }
    inline QPoint getBottomRight() { return mBottomRight; }
    inline void setBottomRight(QPoint bottomRight) { mBottomRight = bottomRight; }

    inline int getWidth() { return getBottomRight().x() - getTopLeft().x() + 1; }
    inline int getHeight() { return getBottomRight().y() - getTopLeft().y() + 1; }
    inline int getMiddleWidth() { return (getTopLeft().x() + getBottomRight().x()) / 2; }
    inline int getMiddleHeight() { return (getTopLeft().y() + getBottomRight().y()) / 2; }
    inline QSize getSize() { return QSize(getWidth(), getHeight()); }

    inline Rgb getColor() { return mColor; }
    inline void setColor(Rgb color) { mColor = color; }

    bool isSize(int size);

    bool hasPoint(double x, double y);
    bool hasPoint(QPoint point);

    static bool isSizeThreshold(Polygon polygon, int threshold);
    static bool isBrightnessThreshold(QImage& image, Polygon& polygon, int threshold);

private:
    QPoint mTopLeft;
    QPoint mBottomRight;
    Rgb mColor;
};

#endif // POLYGON_H

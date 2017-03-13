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

bool Polygon::isSizeThreshold(Polygon polygon, int threshold)
{
    if (polygon.getWidth() <= threshold && polygon.getHeight() <= threshold)
        return true;

    return false;
}

bool Polygon::isBrightnessThreshold(QImage& image, Polygon& polygon, int threshold)
{
    QPoint topLeft = polygon.getTopLeft();
    QPoint bottomRight = polygon.getBottomRight();

    int minimum = 255, maximum = 0;
    for (int x = topLeft.x(); x <= bottomRight.x(); ++x)
      for (int y = topLeft.y(); y <= bottomRight.y(); ++y) {
        int currentBrightness = Rgb(image, QPoint(x, y)).getBrightness();

        minimum = (minimum > currentBrightness) ? currentBrightness : minimum;
        maximum = (maximum < currentBrightness) ? currentBrightness : maximum;
      }

    if (maximum - minimum > threshold)
      return true;

    return false;
}

#include <QColor>

#include "exception.h"
#include "rgb.h"

Rgb::Rgb(int red, int green, int blue)
{
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        throw Exception::ValueError();

    mRed = red;
    mGreen = green;
    mBlue = blue;

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

Rgb::Rgb(QImage& image, QPoint point)
{
    QColor pixelColor = image.pixelColor(point);

    mRed = pixelColor.red();
    mGreen = pixelColor.green();
    mBlue = pixelColor.blue();

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

Rgb::Rgb(QImage& image, QPoint topLeft, QPoint bottomRight)
{
    int area = 0;
    int red = 0, green = 0, blue = 0;

    for (int x = topLeft.x(); x <= bottomRight.x(); ++x)
      for (int y = topLeft.y(); y <= bottomRight.y(); ++y) {
        QColor pixelColor = image.pixelColor(x, y);

        red += pixelColor.red();
        green += pixelColor.green();
        blue += pixelColor.blue();

        ++area;
      }

    mRed = red / area;
    mGreen = green / area;
    mBlue = blue / area;

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

double Rgb::calculateBrightness(int red, int green, int blue)
{
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        throw Exception::ValueError();

    return 0.299 * static_cast<double>(red) +
            0.587 * static_cast<double>(green) +
            0.114 * static_cast<double>(blue);
}

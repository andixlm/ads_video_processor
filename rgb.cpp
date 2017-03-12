#include <QColor>

#include "exception.h"
#include "rgb.h"

Rgb::Rgb(unsigned red, unsigned green, unsigned blue)
{
    if (red > 255 || green > 255 || blue > 255)
        throw Exception::ValueError();

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

Rgb::Rgb(QImage &image, QPoint point)
{
    QColor color = image.pixelColor(point);

    mRed = color.red();
    mGreen = color.green();
    mBlue = color.blue();

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

Rgb::Rgb(QImage& image, QPoint topLeft, QPoint bottomRight)
{
    int area = 0;
    unsigned red = 0;
    unsigned green = 0;
    unsigned blue = 0;

    for (int x = topLeft.x(); x < bottomRight.x(); ++x)
      for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
        QColor color = image.pixelColor(x, y);

        red += color.red();
        green += color.green();
        blue += color.blue();

        ++area;
      }

    mRed = red / area;
    mGreen = green / area;
    mBlue = blue / area;

    mBrightness = calculateBrightness(mRed, mGreen, mBlue);
}

double Rgb::calculateBrightness(unsigned red, unsigned green, unsigned blue)
{
    return 0.299 * red + 0.587 * green + 0.114 * blue;
}

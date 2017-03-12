#include "exception.h"
#include "rgb.h"

Rgb::Rgb(unsigned red, unsigned green, unsigned blue)
{
    if (red > 255 || green > 255 || blue > 255)
        throw Exception::ValueError();

    mBrightness = 0.299 * mRed + 0.587 * mGreen + 0.114 * mBlue;
}

Rgb Rgb::getImageColor(QImage image, QPoint topLeft, QPoint bottomRight)
{
    int area = 0;
    unsigned red = 0;
    unsigned green = 0;
    unsigned blue = 0;

    for (int x = topLeft.x(); x < bottomRight.x(); ++x)
      for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
        red += image.pixelColor(x, y).red();
        green += image.pixelColor(x, y).green();
        blue += image.pixelColor(x, y).blue();

        ++area;
      }

    return Rgb(red / area, green / area, blue / area);
}

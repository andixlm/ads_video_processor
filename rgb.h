#ifndef RGB_H
#define RGB_H

#include <QImage>
#include <QPoint>

class Rgb
{
public:
    Rgb(unsigned red = 0, unsigned green = 0, unsigned blue = 0);

    unsigned getRed() { return mRed; }
    unsigned getGreen() { return mGreen; }
    unsigned getBlue() { return mBlue; }

    int getBrightness() { return static_cast<int>(mBrightness); }

    static Rgb getImageColor(QImage image, QPoint topLeft, QPoint bottomRight);

private:
    unsigned mRed;
    unsigned mGreen;
    unsigned mBlue;

    double mBrightness;
};

#endif // RGB_H

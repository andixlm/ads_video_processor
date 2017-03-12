#ifndef RGB_H
#define RGB_H

#include <QImage>
#include <QPoint>

class Rgb
{
public:
    Rgb(unsigned red = 0, unsigned green = 0, unsigned blue = 0);
    Rgb(QImage& image, QPoint point);
    Rgb(QImage& image, QPoint topLeft, QPoint bottomRight);

    unsigned getRed() { return mRed; }
    void setRed(unsigned red) { mRed = red; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    unsigned getGreen() { return mGreen; }
    void setGreen(unsigned green) { mGreen = green; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    unsigned getBlue() { return mBlue; }
    void setBlue(unsigned blue) { mBlue = blue; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }

    int getBrightness() { return static_cast<int>(mBrightness); }

private:
    unsigned mRed;
    unsigned mGreen;
    unsigned mBlue;

    double mBrightness;
    double calculateBrightness(unsigned red, unsigned green, unsigned blue);
};

#endif // RGB_H

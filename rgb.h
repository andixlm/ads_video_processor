#ifndef RGB_H
#define RGB_H

#include <QImage>
#include <QPoint>

class Rgb
{
public:
    Rgb(int red = 0, int green = 0, int blue = 0);
    Rgb(QImage& image, QPoint point);
    Rgb(QImage& image, QPoint topLeft, QPoint bottomRight);

    inline int getRed() { return mRed; }
    inline void setRed(int red) { mRed = red; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    inline int getGreen() { return mGreen; }
    inline void setGreen(int green) { mGreen = green; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    inline int getBlue() { return mBlue; }
    inline void setBlue(int blue) { mBlue = blue; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }

    inline int getBrightness() { return static_cast<int>(mBrightness); }
    static double calculateBrightness(int red, int green, int blue);

private:
    int mRed;
    int mGreen;
    int mBlue;

    double mBrightness;
};

#endif // RGB_H

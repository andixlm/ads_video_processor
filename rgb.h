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

    int getRed() { return mRed; }
    void setRed(int red) { mRed = red; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    int getGreen() { return mGreen; }
    void setGreen(int green) { mGreen = green; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }
    int getBlue() { return mBlue; }
    void setBlue(int blue) { mBlue = blue; mBrightness = calculateBrightness(mRed, mGreen, mBlue); }

    int getBrightness() { return static_cast<int>(mBrightness); }
    static double calculateBrightness(int red, int green, int blue);

private:
    int mRed;
    int mGreen;
    int mBlue;

    double mBrightness;
};

#endif // RGB_H

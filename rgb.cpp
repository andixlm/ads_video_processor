#include "rgb.h"

Rgb::Rgb(unsigned red, unsigned green, unsigned blue) :
    mRed(red), mGreen(green), mBlue(blue)
{
    mBrightness = 0.299 * mRed + 0.587 * mGreen + 0.114 * mBlue;
}

int Rgb::getBrightness()
{
    return static_cast<int> (mBrightness);
}

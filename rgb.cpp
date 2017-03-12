#include "exception.h"
#include "rgb.h"

Rgb::Rgb(unsigned red, unsigned green, unsigned blue)
{
    if (red > 255 || green > 255 || blue > 255)
        throw Exception::ValueError();

    mBrightness = 0.299 * mRed + 0.587 * mGreen + 0.114 * mBlue;
}

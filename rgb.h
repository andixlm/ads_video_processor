#ifndef RGB_H
#define RGB_H

class Rgb
{
public:
    Rgb(unsigned red = 0, unsigned green = 0, unsigned blue = 0);

    int getBrightness();

private:
    unsigned mRed;
    unsigned mGreen;
    unsigned mBlue;

    double mBrightness;
};

#endif // RGB_H

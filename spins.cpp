#include "imagewindow.h"

void ImageWindow::on_sizeSpin_valueChanged(int value)
{
    mSizeThreshold = value;
}

void ImageWindow::on_brightnessSpin_valueChanged(int value)
{
    mBrightnessThreshold = value;
}

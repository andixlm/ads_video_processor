#include <imagewindow.h>

namespace Mode {
    enum { buildGrid, restoreImage };
}

void ImageWindow::on_modeBox_currentIndexChanged(int value)
{
    switch (value) {
    case Mode::buildGrid:
        processImage = &buildGrid;
        break;
    case Mode::restoreImage:
        processImage = &restoreImage;
        break;
    }
}

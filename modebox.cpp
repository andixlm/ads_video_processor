#include <imageview.h>

namespace Mode {
    enum { buildGrid };
}

void ImageView::on_modeBox_currentIndexChanged(int value)
{
    switch (value) {
    case Mode::buildGrid:
        processImage = &buildGrid;
        break;
    }
}

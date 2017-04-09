#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>

#include "polygon.h"

namespace Tools {
    QImage getBlankImage(QSize size);

    void drawPolygon(QImage& image, Polygon& polygon);
    void fillPolygon(QImage& image, Polygon& polygon);
}

#endif // TOOLS_H

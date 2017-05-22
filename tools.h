#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>

#include "polygon.h"

namespace Tools {
    QImage getBlankImage(QSize size);

    void drawPolygon(QImage& image, Polygon& polygon, int color);
    void drawPolygons(QImage& image, QVector<Polygon*>* polygons, int color);
    void fillPolygon(QImage& image, Polygon& polygon);
    void fillPolygons(QImage& image, QVector<Polygon*>* polygons);
}

#endif // TOOLS_H

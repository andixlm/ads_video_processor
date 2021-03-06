#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QSize>
#include <QVector>

#include "polygon.h"

namespace Tools {
    QImage getBlankImage(QSize size);

    void drawPolygon(QImage& image, Polygon& polygon, int color = Qt::black);
    void drawPolygons(QImage& image, QVector<Polygon*>* polygons, int color = Qt::black);

    void fillPolygon(QImage& image, Polygon& polygon);
    void fillPolygons(QImage& image, QVector<Polygon*>* polygons);
}

#endif // TOOLS_H

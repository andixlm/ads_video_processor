#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QSize>

#include "polygon.h"
#include "rgb.h"
#include "tools.h"

QImage Tools::getBlankImage(QSize size)
{
    QImage image = QImage(QPixmap(size).toImage());
    image.fill(Qt::white);

    return image;
}

void Tools::drawPolygon(QImage& image, Polygon& polygon, int color)
{
    QPoint topLeft = polygon.getTopLeft();
    QPoint bottomRight = polygon.getBottomRight();

    QPainter painter;

    painter.begin(&image);
    painter.setPen(QColor(color));
    painter.drawRect(QRect(topLeft, bottomRight));
    painter.end();
}

void Tools::drawPolygons(QImage& image, QVector<Polygon*>* polygons, int color)
{
    if (!polygons)
        return;

    for (QVector<Polygon*>::const_iterator polygon = polygons->begin(), end = polygons->end(); polygon != end; ++polygon) {
        Tools::drawPolygon(image, **polygon, color);
    }
}

void Tools::fillPolygon(QImage& image, Polygon& polygon)
{
    QPainter painter;
    Rgb polygonColor = polygon.getColor();

    painter.begin(&image);
    painter.fillRect(QRect(polygon.getTopLeft(), polygon.getBottomRight()),
                     QColor(polygonColor.getRed(), polygonColor.getGreen(), polygonColor.getBlue()));
    painter.end();
}

void Tools::fillPolygons(QImage& image, QVector<Polygon*>* polygons)
{
    if (!polygons)
        return;

    for (QVector<Polygon*>::const_iterator polygon = polygons->begin(), end = polygons->end(); polygon != end; ++polygon) {
        Tools::fillPolygon(image, **polygon);
    }
}

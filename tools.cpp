#include <QPainter>
#include <QPixmap>

#include "tools.h"

QImage Tools::getBlankImage(QSize size)
{
    QImage image = QImage(QPixmap(size).toImage());
    image.fill(Qt::white);

    return image;
}

void Tools::drawPolygon(QImage& image, Polygon& polygon)
{
    QPoint topLeft = polygon.getTopLeft();
    QPoint bottomRight = polygon.getBottomRight();

    QPainter painter;
    painter.begin(&image);
    painter.setPen(QColor(Qt::black));

    painter.drawRect(QRect(topLeft, bottomRight));

    painter.end();
}

void Tools::fillPolygon(QImage& image, Polygon& polygon)
{
    QPainter painter;
    painter.begin(&image);
    painter.fillRect(QRect(polygon.getTopLeft(), polygon.getBottomRight()),
                     QColor(polygon.getColor().getRed(), polygon.getColor().getGreen(), polygon.getColor().getBlue()));
    painter.end();
}

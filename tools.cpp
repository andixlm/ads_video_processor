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

    painter.drawLine(topLeft.x(), topLeft.y(), bottomRight.x(), topLeft.y());
    painter.drawLine(bottomRight.x(), topLeft.y(), bottomRight.x(), bottomRight.y());
    painter.drawLine(bottomRight.x(), bottomRight.y(), topLeft.x(), bottomRight.y());
    painter.drawLine(topLeft.x(), bottomRight.y(), topLeft.x(), topLeft.y());

    painter.end();
}

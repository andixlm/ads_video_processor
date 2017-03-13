#include <QPixmap>

#include "tools.h"

QImage Tools::getBlankImage(QSize size)
{
    QImage image = QImage(QPixmap(size).toImage());
    image.fill(Qt::white);

    return image;
}

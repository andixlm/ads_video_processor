#include <QPixmap>

#include "imagewindow.h"
#include "ui_imagewindow.h"

void ImageWindow::buildGrid()
{
    mImageTree.clear();

    _buildGrid(Polygon(mOriginalImage, QPoint(), QPoint(mOriginalImage.width() - 1, mOriginalImage.height() - 1)));

    mStagedImage = mImageTree.toImageGrid();

    if (mStagedImage.width() > mStagedImage.height())
        ui->stagedImage->setPixmap(QPixmap::fromImage(mStagedImage).scaledToWidth(Ui::FRAME_SIZE));
    else
        ui->stagedImage->setPixmap(QPixmap::fromImage(mStagedImage).scaledToHeight(Ui::FRAME_SIZE));
}

void ImageWindow::_buildGrid(Polygon polygon)
{
    mImageTree.insert(polygon);

    if (!Polygon::isSizeThreshold(polygon, mSizeThreshold) &&
            Polygon::isBrightnessThreshold(mOriginalImage, polygon, mBrightnessThreshold)) {
        int width = polygon.getWidth();
        int height = polygon.getHeight();
        int middleWidth = polygon.getMiddleWidth();
        int middleHeight = polygon.getMiddleHeight();

        if (width >= height) {
            // Divide with vertical line.
            _buildGrid(Polygon(mOriginalImage,
                               polygon.getTopLeft(),
                               QPoint(middleWidth, polygon.getBottomRight().y())));

            _buildGrid(Polygon(mOriginalImage,
                               QPoint(middleWidth + 1, polygon.getTopLeft().y()),
                               polygon.getBottomRight()));
        } else {
            // Devide with horizontal line.
            _buildGrid(Polygon(mOriginalImage,
                               polygon.getTopLeft(),
                               QPoint(polygon.getBottomRight().x(), middleHeight)));

            _buildGrid(Polygon(mOriginalImage,
                               QPoint(polygon.getTopLeft().x(), middleHeight + 1),
                               polygon.getBottomRight()));
        }
    }
}

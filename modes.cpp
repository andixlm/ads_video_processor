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

    int polygonsNumber = mImageTree.getPolygonsNumber();
    ui->polygonsNumberValue->setText(QString::number(polygonsNumber));
    ui->compressionCoefficientValue->setText(QString::number(static_cast<double>(mOriginalImage.width() * mOriginalImage.height()) /
                                                             static_cast<double>(polygonsNumber)));
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

void ImageWindow::restoreImage()
{
    if (mImageTree.isEmpty())
        return;

    mFinalImage = mImageTree.toImage();

    if (mFinalImage.width() > mFinalImage.height())
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToWidth(Ui::FRAME_SIZE));
    else
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToHeight(Ui::FRAME_SIZE));
}

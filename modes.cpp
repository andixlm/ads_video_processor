#include <QtMath>
#include <QPixmap>
#include <QPoint>
#include <QString>

#include "imagewindow.h"
#include "polygon.h"
#include "rgb.h"
#include "ui_imagewindow.h"

void ImageWindow::buildGrid()
{
    mImageTree.clear();

    _buildGrid(Polygon(mOriginalImage, QPoint(), QPoint(mOriginalImage.width() - 1, mOriginalImage.height() - 1)));

    mStagedImage = mImageTree.toImageGrid();

    if (mStagedImage.width() > mStagedImage.height())
        ui->stagedImage->setPixmap(QPixmap::fromImage(mStagedImage).scaledToWidth(Ui::FRAME_SIZE, Qt::SmoothTransformation));
    else
        ui->stagedImage->setPixmap(QPixmap::fromImage(mStagedImage).scaledToHeight(Ui::FRAME_SIZE, Qt::SmoothTransformation));

    int polygonsNumber = mImageTree.getPolygonsNumber();
    ui->polygonsNumberValue->setText(QString::number(polygonsNumber));
    ui->compressionCoefficientValue->setText(QString::number(static_cast<double>(mOriginalImage.width() * mOriginalImage.height()) /
                                                             static_cast<double>(polygonsNumber)));

    // Restore image.
    mFinalImage = mImageTree.toImage();

    if (mFinalImage.width() > mFinalImage.height())
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToWidth(Ui::FRAME_SIZE, Qt::SmoothTransformation));
    else
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToHeight(Ui::FRAME_SIZE, Qt::SmoothTransformation));

    // Calculate standart deviation.
    double deviation = 0.0;
    for (int x = 0; x <= mOriginalImage.width() - 1; ++x)
        for (int y = 0; y <= mOriginalImage.height() - 1; ++y)
            deviation += qPow(static_cast<double>(Rgb(mOriginalImage, QPoint(x, y)).getBrightness()) -
                              static_cast<double>(Rgb(mFinalImage, QPoint(x, y)).getBrightness()), 2.0);

    ui->standartDeviationValue->setText(QString::number(qSqrt(deviation / (mOriginalImage.width() * mOriginalImage.height()))));
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
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToWidth(Ui::FRAME_SIZE, Qt::SmoothTransformation));
    else
        ui->finalImage->setPixmap(QPixmap::fromImage(mFinalImage).scaledToHeight(Ui::FRAME_SIZE, Qt::SmoothTransformation));
}

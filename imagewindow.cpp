#include <QPixmap>

#include "imagewindow.h"
#include "ui_imagewindow.h"

ImageWindow::ImageWindow(QWidget* parent, QImage image) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow)
{
    ui->setupUi(this);

    processImage = &ImageWindow::buildGrid;

    mSizeThreshold = ui->sizeSpin->value();
    mBrightnessThreshold = ui->brightnessSpin->value();

    mOriginalImage = image;
    mStagedImage = getBlankImage(mOriginalImage.size());
    mFinalImage = getBlankImage(mOriginalImage.size());

    if (mOriginalImage.width() > mOriginalImage.height())
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToWidth(Ui::FRAME_SIZE));
    else
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToHeight(Ui::FRAME_SIZE));
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

void ImageWindow::buildGrid()
{
    _buildGrid(Polygon(mOriginalImage, QPoint(), QPoint(mOriginalImage.width() - 1, mOriginalImage.height() - 1)));
}

void ImageWindow::_buildGrid(Polygon polygon)
{
    mImageTree.insert(polygon);

    if (Polygon::isSizeThreshold(polygon, mSizeThreshold) &&
            Polygon::isBrightnessThreshold(mOriginalImage, polygon, mBrightnessThreshold)) {
        int width = polygon.getWidth();
        int height = polygon.getHeight();
        int middleWidth = polygon.getMiddleWidth();
        int middleHeight = polygon.getMiddleHeight();

        if (width > height) {
            // Divide with vertical line.
            _buildGrid(Polygon(mOriginalImage,
                               polygon.getTopLeft(),
                               QPoint(middleWidth, polygon.getBottomRight().y())));

            _buildGrid(Polygon(mOriginalImage,
                               QPoint(middleHeight + 1, polygon.getTopLeft().y()),
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

QImage ImageWindow::getBlankImage(QSize size)
{
    QImage image = QImage(QPixmap(size).toImage());
    image.fill(Qt::white);

    return image;
}

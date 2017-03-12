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
    return;
}

QImage ImageWindow::getBlankImage(QSize size)
{
    QImage image = QImage(QPixmap(size).toImage());
    image.fill(Qt::white);

    return image;
}

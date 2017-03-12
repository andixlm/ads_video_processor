#include <QPixmap>

#include "imagewindow.h"
#include "ui_imagewindow.h"

ImageWindow::ImageWindow(QWidget* parent, QImage image) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow)
{
    ui->setupUi(this);

    processImage = &ImageWindow::buildGrid;

    mSizeThreshold = ui->sizeBox->value();
    mBrightnessThreshold = ui->brightnessBox->value();

    mOriginalImage = image;
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

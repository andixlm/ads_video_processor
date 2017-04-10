#include <QPixmap>

#include "imagewindow.h"
#include "ui_imagewindow.h"

ImageWindow::ImageWindow(QWidget* parent, QImage image) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow)
{
    ui->setupUi(this);
    fullSizeImageWindow = nullptr;

    processImage = &ImageWindow::buildGrid;

    mSizeThreshold = ui->sizeSpin->value();
    mBrightnessThreshold = ui->brightnessSpin->value();

    mOriginalImage = image;

    if (mOriginalImage.width() > mOriginalImage.height())
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToWidth(Ui::FRAME_SIZE));
    else
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToHeight(Ui::FRAME_SIZE));
}

FullSizeImageWindow::FullSizeImageWindow(QWidget* parent, QImage image) :
    QMainWindow(parent)
{
    mImageFrame.setParent(this);
    mImageFrame.setGeometry(0, 0, image.width(), image.height());
    mImageFrame.setPixmap(QPixmap::fromImage(image));

    this->setFixedSize(image.width(), image.height());
    this->show();
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

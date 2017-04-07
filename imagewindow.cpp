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

FullSizeImageWindow::FullSizeImageWindow(QImage& image)
{
    mImageFrame.setWindowTitle(tr("Full size image"));
    mImageFrame.setFixedSize(image.width(), image.height());
    mImageFrame.setPixmap(QPixmap::fromImage(image));
    mImageFrame.show();
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

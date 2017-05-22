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
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToWidth(Ui::FRAME_SIZE, Qt::SmoothTransformation));
    else
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToHeight(Ui::FRAME_SIZE, Qt::SmoothTransformation));
}

FullSizeImageWindow::FullSizeImageWindow(QWidget* parent, QImage image) :
    QMainWindow(parent),
    mParentImageWindow(static_cast<ImageWindow*>(parent))
{
    connect(&mClickableImageFrame, &ClickableLabel::clicked,
            this, &FullSizeImageWindow::mouseButtonPressed);

    mStaticImage = Tools::getBlankImage(QSize(image.size()));
    mClickableImage = image;

    mStaticImageFrame.setParent(this);
    mStaticImageFrame.setGeometry(0, 0, image.width(), image.height());
    mStaticImageFrame.setPixmap(QPixmap::fromImage(mStaticImage));

    mClickableImageFrame.setParent(this);
    mClickableImageFrame.setGeometry(image.width() + offset, 0, 2 * image.width() + offset, image.height());
    mClickableImageFrame.setPixmap(QPixmap::fromImage(mClickableImage));

    this->setFixedSize(2 * image.width() + offset, image.height());
    this->show();
}

void FullSizeImageWindow::mouseButtonPressed(QMouseEvent* event)
{
    return;
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

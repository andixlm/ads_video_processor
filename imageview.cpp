#include <QPixmap>

#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget* parent, QImage image) :
    QWidget(parent),
    ui(new Ui::ImageView),
    mOriginalImage(image)
{
    ui->setupUi(this);

    processImage = &ImageView::buildGrid;

    if (mOriginalImage.width() > mOriginalImage.height())
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToWidth(Ui::FRAME_SIZE));
    else
        ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToHeight(Ui::FRAME_SIZE));
}

ImageView::~ImageView()
{
    delete ui;
}

void ImageView::buildGrid()
{
    return;
}

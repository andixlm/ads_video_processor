#include <QPixmap>

#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget* parent, QImage image) :
    QWidget(parent),
    ui(new Ui::ImageView),
    mOriginalImage(image)
{
    ui->setupUi(this);
    ui->originalImage->setPixmap(QPixmap::fromImage(mOriginalImage).scaledToWidth(Ui::FRAME_SIZE));
}

ImageView::~ImageView()
{
    delete ui;
}

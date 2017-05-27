#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPoint>
#include <QSize>
#include <QWidget>

#include "imagewindow.h"
#include "polygon.h"
#include "ui_imagewindow.h"

const char infoText[] =
        "Инструкция: Для выделения областей на изображении, кликните на правое изображение и ожидайте окончания работы.\n"
        "Для изменения типа отрисовки, кликните на левое изображение.";

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
    connect(&mNewImageFrame, &ClickableLabel::clicked,
            this, &FullSizeImageWindow::clickedNewImage);

    connect(&mCurrentImageFrame, &ClickableLabel::clicked,
            this, &FullSizeImageWindow::clickedCurrentImage);

    mNewImage = Tools::getBlankImage(QSize(image.size()));

    if (!mParentImageWindow->mSelectedPolygons.empty())
    {
        if (mFillPolygons)
            Tools::fillPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);
        else
            Tools::drawPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);
    }

    mCurrentImage = image;

    mNewImageFrame.setParent(this);
    mNewImageFrame.setGeometry(0, 6 * offset, image.width(), image.height());
    mNewImageFrame.setPixmap(QPixmap::fromImage(mNewImage));

    mCurrentImageFrame.setParent(this);
    mCurrentImageFrame.setGeometry(image.width() + offset, 6 * offset, 2 * image.width() + offset, image.height());
    mCurrentImageFrame.setPixmap(QPixmap::fromImage(mCurrentImage));

    mInfoLabel.setParent(this);
    mInfoLabel.setGeometry(offset, offset, 2 * image.width() + offset, 4 * offset);
    mInfoLabel.setText(infoText);

    this->setFixedSize(2 * image.width() + offset, image.height() + 6 * offset);
    this->show();
}

void FullSizeImageWindow::clickedNewImage()
{
    mFillPolygons = !mFillPolygons;

    mNewImage = Tools::getBlankImage(mNewImage.size());

    if (mFillPolygons)
        Tools::fillPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);
    else
        Tools::drawPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);

    mNewImageFrame.setPixmap(QPixmap::fromImage(mNewImage));
}

void FullSizeImageWindow::clickedCurrentImage(QMouseEvent* event)
{
    Polygon* selectedPolygon = mParentImageWindow->mImageTree.getPolygonByPoint(QPoint(event->x(), event->y()));
    if (!selectedPolygon)
        return;

    mParentImageWindow->mImageTree.getAllAdjacentPolygonsByBrightness(selectedPolygon,
                                                                      selectedPolygon->getColor().getBrightness(),
                                                                      mParentImageWindow->mBrightnessThreshold,
                                                                      &mParentImageWindow->mSelectedPolygons);

    if (mFillPolygons)
        Tools::fillPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);
    else
        Tools::drawPolygons(mNewImage, &mParentImageWindow->mSelectedPolygons);

    mNewImageFrame.setPixmap(QPixmap::fromImage(mNewImage));
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

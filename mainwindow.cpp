#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QString>

#include "mainwindow.h"
#include "player.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPlayer = new Player(this);
    connect(mPlayer, &Player::processedImage,
            this, &MainWindow::updatePlayerUI);
    connect(mPlayer, &Player::emptyImage,
            this, &MainWindow::resetPlayerUI);
}

MainWindow::~MainWindow()
{
    if (mImageWindow)
        delete mImageWindow;
    delete mPlayer;
    delete ui;
}

QImage MainWindow::getCurrentFrame()
{
    return ui->videoFrame->pixmap() ? ui->videoFrame->pixmap()->toImage() : QImage();
}

void MainWindow::updatePlayerUI(QImage image)
{
    if (!image.isNull()) {
        ui->videoFrame->setAlignment(Qt::AlignCenter);
        ui->videoFrame->setPixmap(QPixmap::fromImage(image).scaled(ui->videoFrame->size(),
                                                                   Qt::KeepAspectRatio,
                                                                   Qt::FastTransformation));
    }
}

void MainWindow::resetPlayerUI()
{
    ui->videoFrame->setPixmap(QPixmap::fromImage(QImage()));
}

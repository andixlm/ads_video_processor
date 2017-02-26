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
}

MainWindow::~MainWindow()
{
    delete mPlayer;
    delete ui;
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

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

    player = new Player;
    connect(player, &Player::processedImage,
            this, &MainWindow::updatePlayerUI);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".",
                                                    tr("*.avi *.mp4 *.mpg"));

    if (!fileName.isEmpty())
        player->loadVideo(fileName.toStdString());
}

void MainWindow::on_playButton_clicked()
{
    if (player->isStopped())
        player->play();
}

void MainWindow::on_stopButton_clicked()
{
    if (!player->isStopped())
        player->stop();
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

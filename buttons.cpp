#include "mainwindow.h"
#include "ui_imagewindow.h"

void MainWindow::on_playButton_clicked()
{
    if (mPlayer->isStopped())
        mPlayer->play();
}

void MainWindow::on_pauseButton_clicked()
{
    if (!mPlayer->isStopped())
        mPlayer->pause();
}

void MainWindow::on_stopButton_clicked()
{
    mPlayer->stop();
}

void ImageWindow::on_openOriginalImage_clicked()
{
    return;
}

void ImageWindow::on_openStagedImage_clicked()
{
    return;
}

void ImageWindow::on_openFinalImage_clicked()
{
    return;
}

void ImageWindow::on_runButton_clicked()
{
    (this->*processImage)();
}

void ImageWindow::on_clearButton_clicked()
{
    ui->stagedImage->clear();
    ui->finalImage->clear();
}

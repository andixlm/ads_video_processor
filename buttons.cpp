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
    if (!ui->originalImage->pixmap())
        return;

    fullSizeImageWindow = new FullSizeImageWindow(mOriginalImage);
}

void ImageWindow::on_openStagedImage_clicked()
{
    if (!ui->stagedImage->pixmap())
        return;

    fullSizeImageWindow = new FullSizeImageWindow(mStagedImage);
}

void ImageWindow::on_openFinalImage_clicked()
{
    if (!ui->finalImage->pixmap())
        return;

    fullSizeImageWindow = new FullSizeImageWindow(mFinalImage);
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

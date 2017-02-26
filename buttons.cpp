#include "mainwindow.h"

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
    on_pauseButton_clicked();

    mPlayer->stop();
}

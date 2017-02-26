#include "mainwindow.h"

void MainWindow::on_playButton_clicked()
{
    if (mPlayer->isStopped())
        mPlayer->play();
}

void MainWindow::on_stopButton_clicked()
{
    if (!mPlayer->isStopped())
        mPlayer->stop();
}

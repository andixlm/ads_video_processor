#include <QApplication>
#include <QFileDialog>

#include "mainwindow.h"

void MainWindow::on_actionOpen_triggered()
{
    if (!mPlayer->isStopped())
        mPlayer->pause();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("*.avi"));

    if (!fileName.isEmpty()) {
        mPlayer->closeVideo();
        mPlayer->loadVideo(fileName.toStdString());
    }
}

void MainWindow::on_actionClose_triggered()
{
    mPlayer->closeVideo();
}

void MainWindow::on_actionExit_triggered()
{
    if (!mPlayer->isStopped())
        mPlayer->pause();

    mPlayer->closeVideo();
    QApplication::exit();
}

void MainWindow::on_actionUnpackVideo_triggered()
{
    if (!mPlayer->isOpened())
        return;

    if (!mPlayer->isStopped())
        mPlayer->pause();

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));
    if (!dirName.isEmpty())
        mPlayer->unpackVideo(dirName.toStdString());
}

void MainWindow::on_actionOpenCurrentFrame_triggered()
{
    QImage currentFrame = getCurrentFrame();
    if (currentFrame.isNull())
        return;

    if (!mPlayer->isStopped())
        mPlayer->pause();

    if (mImageWindow)
        delete mImageWindow;
    mImageWindow = new ImageWindow(this, currentFrame);
    mImageWindow->setFixedSize(mImageWindow->width(), mImageWindow->height());
    mImageWindow->show();
}

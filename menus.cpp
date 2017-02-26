#include "mainwindow.h"

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".",
                                                    tr("*.avi"));

    if (!fileName.isEmpty())
        mPlayer->loadVideo(fileName.toStdString());
}

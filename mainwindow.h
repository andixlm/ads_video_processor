#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>

#include "imagewindow.h"
#include "player.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    Player* mPlayer;
    ImageWindow* mImageWindow;

    QImage getCurrentFrame();

private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();

    void on_actionUnpackVideo_triggered();
    void on_actionOpenCurrentFrame_triggered();

    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();

    void updatePlayerUI(QImage image);
    void resetPlayerUI();
};

#endif // MAINWINDOW_H

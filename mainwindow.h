#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>

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

private slots:
    void on_actionOpen_triggered();

    void on_playButton_clicked();
    void on_stopButton_clicked();

    void updatePlayerUI(QImage);
};

#endif // MAINWINDOW_H

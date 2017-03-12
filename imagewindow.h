#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QImage>

namespace Ui {
    class ImageWindow;

    const int FRAME_SIZE = 249;
}

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget* parent = nullptr, QImage image = QImage());
    ~ImageWindow();

private:
    Ui::ImageWindow *ui;

    QImage mOriginalImage;

    void (ImageWindow::* processImage)();
    void buildGrid();

    void on_openOriginalImage_clicked();
    void on_openStagedImage_clicked();
    void on_openFinalImage_clicked();

    void on_modeBox_currentIndexChanged(int value);
};

#endif // IMAGEWINDOW_H

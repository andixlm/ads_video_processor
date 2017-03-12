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

    int mSizeThreshold;
    int mBrightnessThreshold;

    QImage mOriginalImage;
    QImage mStagedImage;
    QImage mFinalImage;

    void (ImageWindow::* processImage)();
    void buildGrid();

    QImage getBlankImage(QSize size);

    void on_openOriginalImage_clicked();
    void on_openStagedImage_clicked();
    void on_openFinalImage_clicked();

private slots:
    void on_modeBox_currentIndexChanged(int value);

    void on_sizeSpin_valueChanged(int value);
    void on_brightnessSpin_valueChanged(int value);
};

#endif // IMAGEWINDOW_H

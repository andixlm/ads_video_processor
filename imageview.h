#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QImage>

namespace Ui {
    class ImageView;

    const int FRAME_SIZE = 249;
}

class ImageView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageView(QWidget* parent = nullptr, QImage image = QImage());
    ~ImageView();

private:
    Ui::ImageView* ui;

    QImage mOriginalImage;

    void (ImageView::* processImage)();
    void buildGrid();

    void on_modeBox_currentIndexChanged(int value);
};

#endif // IMAGEVIEW_H

#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

namespace Ui {
    class ImageView;
}

class ImageView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageView(QWidget* parent = nullptr);
    ~ImageView();

private:
    Ui::ImageView* ui;
};

#endif // IMAGEVIEW_H

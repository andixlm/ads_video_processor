#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

protected:
    void mousePressEvent(QMouseEvent* event);

signals:
    void clicked(QMouseEvent* event);
};

#endif // CLICKABLEQLABEL_H

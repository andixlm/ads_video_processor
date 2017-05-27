#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

#include "clickablelabel.h"
#include "imagewindow.h"

ClickableLabel::ClickableLabel(QWidget* parent) :
    QLabel(parent)
{

}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(event);
}

#include "rect.h"
#include "QPainter"

Rect::Rect(QWidget *parent)
    : Shape{parent}
{
    setFixedSize(RECT_SIZE+2*BRUSH_ACTIVE, RECT_SIZE+2*BRUSH_ACTIVE);
}

void Rect::paintEvent(QPaintEvent *ev)
{
    QWidget::paintEvent(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(color));
    if(dragging){
        painter.setPen(QPen(Qt::black,BRUSH_ACTIVE));
    } else{
        painter.setPen(QPen(Qt::black,BRUSH_NON_ACTIVE));
    }
    //painter.fillRect(QRect(BRUSH_ACTIVE,BRUSH_ACTIVE,RECT_SIZE,RECT_SIZE), painter.brush());
    painter.drawRect(QRect(BRUSH_ACTIVE,BRUSH_ACTIVE,RECT_SIZE,RECT_SIZE));
}


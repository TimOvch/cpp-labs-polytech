#include "ellipse.h"
#include "QPainter"

Ellipse::Ellipse(QWidget *parent)
    : Shape{parent}
{
    setFixedSize(ELLIPSE_X_SIZE+2*BRUSH_ACTIVE, ELLIPSE_Y_SIZE+2*BRUSH_ACTIVE);
}

void Ellipse::paintEvent(QPaintEvent *ev)
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
    painter.drawEllipse(QRect(BRUSH_ACTIVE, BRUSH_ACTIVE, ELLIPSE_X_SIZE, ELLIPSE_Y_SIZE));
}

#include "triangle.h"
#include "QPainter"

Triangle::Triangle(QWidget *parent)
    : Shape{parent}
{
    setFixedSize(1.5*TRIANGLE_SIZE + 2*BRUSH_ACTIVE, TRIANGLE_SIZE +2*BRUSH_ACTIVE);
}

void Triangle::paintEvent(QPaintEvent *ev)
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

    QPolygon triangle;
    triangle << QPoint(0.75*TRIANGLE_SIZE+BRUSH_ACTIVE, BRUSH_ACTIVE)
             << QPoint(BRUSH_ACTIVE, TRIANGLE_SIZE + BRUSH_ACTIVE)
             << QPoint(1.5*TRIANGLE_SIZE + BRUSH_ACTIVE, TRIANGLE_SIZE + BRUSH_ACTIVE);
    painter.drawPolygon(triangle);
}


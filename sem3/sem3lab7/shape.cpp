#include "shape.h"
#include <QMouseEvent>
#include "QRandomGenerator"

Shape::Shape(QWidget *parent)
    : QWidget{parent}, dragging(0)
{
    int red = 128 + QRandomGenerator::global()->bounded(100);
    int green = 128 + QRandomGenerator::global()->bounded(100);
    int blue = 128 + QRandomGenerator::global()->bounded(100);
    color = QColor(red, green, blue);
}

void Shape::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        raise();
        dragging = true;
        emit Activated(this);
        lastMousePosition = event->globalPos() - pos();
    }
}

void Shape::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        QPoint newPos = event->globalPos() - lastMousePosition;
        move(newPos);
    }
}

void Shape::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        update();
    }
}

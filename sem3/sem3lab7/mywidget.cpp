#include "mywidget.h"
#include <QPainter>
#include <QCursor>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), isDragging(false), index(-1)
{
    setFixedSize(600,600);


}

void MyWidget::paintEvent(QPaintEvent *event) {


void MyWidget::mousePressEvent(QMouseEvent *event)
{

}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

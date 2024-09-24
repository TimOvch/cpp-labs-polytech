#include "mywidget.h"
#include <QPainter>
#include <QCursor>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), isDragging(false), index(-1)
{
    setFixedSize(400,400);

    regions.append(new QRegion(QRect(50,50, 100, 100)));
    regions.append(new QRegion(QRect(100,100, 150, 150)));
    regions.append(new QRegion(QRect(150,150, 200, 200)));
}

void MyWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::cyan);

    for (int i = 0; i < regions.length(); i++) {
        if(i%3==0){
            painter.drawRect(regions[i]->boundingRect());
        } else if (i%3 == 1){
            painter.drawEllipse(regions[i]->boundingRect());
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    for(int i =0 ;i < regions.size(); i++){
        if(regions[i]->contains(event->pos())){
            index = i;
            offset = event->pos() - regions[i]->boundingRect().center();
            isDragging = true;
            break;
        }
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging && index!=-1){
        QPoint lb = regions[index]->boundingRect().center();
        regions[i].translate(event->pos() - lb - offset);
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

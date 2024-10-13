#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(400, 400);

    lbl = new QLabel("Hello, World!");
    exitB = new QPushButton("Exit button");
    inner1 = new QWidget(this);
    inner2 = new QWidget(this);

    QPalette pall1;
    pall1.setColor(inner1->backgroundRole(), Qt::blue);
    inner1->setPalette(pall1);
    inner1->setGeometry(10, 10, 100, 100);
    inner1->setAutoFillBackground(true);


    QPalette pall2;
    pall2.setColor(inner2->backgroundRole(), Qt::green);
    inner2->setPalette(pall2);
    inner2->setGeometry(100, 100, 120, 120);
    inner2->setAutoFillBackground(true);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(lbl);
    pvbxLayout->addWidget(exitB);

    setLayout(pvbxLayout);

    connect(exitB, &QPushButton::pressed, this, &QWidget::close);


}

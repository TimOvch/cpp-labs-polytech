#include "shapeswindow.h"
#include "QRandomGenerator"
#include <QMessageBox>

ShapesWindow::ShapesWindow(QWidget *parent)
    : QWidget{parent}, activeShape{nullptr}
{
    setFixedSize(1280,720);

    QWidget *tabWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(tabWidget);

    QPushButton* addRect = new QPushButton("Add rect");
    QPushButton* addEllipse = new QPushButton("Add ellipse");
    QPushButton* addTriangle = new QPushButton("Add triangle");
    QPushButton* deleteActive = new QPushButton("Delete Active");

    buttonLayout->addWidget(addRect);
    buttonLayout->addWidget(addEllipse);
    buttonLayout->addWidget(addTriangle);
    buttonLayout->addWidget(deleteActive);

    connect(deleteActive, &QPushButton::clicked, this, &ShapesWindow::DeleteActiveShape);
    connect(addRect, &QPushButton::clicked, this, &ShapesWindow::addRect);
    connect(addEllipse, &QPushButton::clicked, this, &ShapesWindow::addEllipse);
    connect(addTriangle, &QPushButton::clicked, this, &ShapesWindow::addTriangle);

    tabWidget->setFixedSize(450,50);
    tabWidget->move(0,0);
    tabWidget->show();

    Rect* starterRect = new Rect(this);
    starterRect->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(starterRect, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << starterRect;

    Ellipse* starterEllipse = new Ellipse(this);
    starterEllipse->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(starterEllipse, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << starterEllipse;

    Triangle* starterTriangle = new Triangle(this);
    starterTriangle->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(starterTriangle, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << starterTriangle;
}

void ShapesWindow::Activated(Shape *act)
{
    activeShape = act;
}

void ShapesWindow::DeleteActiveShape()
{
    if(activeShape!=nullptr){
        int id = shapes.indexOf(activeShape);
        delete shapes[id];
        shapes.removeAt(id);
    }
}

void ShapesWindow::addRect()
{
    Rect* rect = new Rect(this);
    rect->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(rect, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << rect;
    rect->show();
}

void ShapesWindow::addEllipse()
{
    Ellipse* ellipse = new Ellipse(this);
    ellipse->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(ellipse, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << ellipse;
    ellipse->show();
}

void ShapesWindow::addTriangle(){
    Triangle* starterTriangle = new Triangle(this);
    starterTriangle->move(QRandomGenerator::global()->bounded(1280-RECT_SIZE),QRandomGenerator::global()->bounded(720-RECT_SIZE));
    connect(starterTriangle, &Shape::Activated, this, &ShapesWindow::Activated);
    shapes << starterTriangle;
    starterTriangle->show();
}

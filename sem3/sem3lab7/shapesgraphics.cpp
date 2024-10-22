
#include "shapesgraphics.h"
#include "QGraphicsRectItem"
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QHBoxLayout>
#include <QPushButton>
#include "QRandomGenerator"
#include <QColor>
#include <QMessageBox>
#include <QPointF>

ShapesGraphics::ShapesGraphics(QWidget* parent)
    : QGraphicsView(parent), lastActiveItem(nullptr)
{
    setFixedSize(1280,720);

    QWidget *tabWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(tabWidget);

    QPushButton* addRect = new QPushButton("Add rect");
    QPushButton* addEllipse = new QPushButton("Add ellipse");
    QPushButton* addTriangle = new QPushButton("Add triangle");
    QPushButton* deleteActive = new QPushButton("Delete Item");

    connect(deleteActive, &QPushButton::clicked, this, &ShapesGraphics::deleteItem);
    connect(addRect, &QPushButton::clicked, this, &ShapesGraphics::addRect);
    connect(addEllipse, &QPushButton::clicked, this, &ShapesGraphics::addEllipse);
    connect(addTriangle, &QPushButton::clicked, this, &ShapesGraphics::addTriangle);


    buttonLayout->addWidget(addRect);
    buttonLayout->addWidget(addEllipse);
    buttonLayout->addWidget(addTriangle);
    buttonLayout->addWidget(deleteActive);

    tabWidget->setFixedSize(450,50);
    tabWidget->move(0,0);
    tabWidget->show();

    scene = new QGraphicsScene(this);
    setScene(scene);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    setGeometry(0, 50, 1280, 670);
    setRenderHint(QPainter::Antialiasing);

    QGraphicsRectItem* pRectitem = scene->addRect(QRectF(-30, -30, 120, 80),QPen(Qt::black), QBrush(Qt::green));
    pRectitem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastActiveItem = scene->itemAt(mapToScene(event->pos()), QTransform());
        if (lastActiveItem) {
            QPointF pos = lastActiveItem->pos();
            scene->removeItem(lastActiveItem);
            scene->addItem(lastActiveItem);
            lastActiveItem->setPos(pos);
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void ShapesGraphics::addRect()
{
    int red = 128 + QRandomGenerator::global()->bounded(100);
    int green = 128 + QRandomGenerator::global()->bounded(100);
    int blue = 128 + QRandomGenerator::global()->bounded(100);
    QColor color = QColor(red, green, blue);

    QGraphicsRectItem* pRectitem = scene->addRect(QRectF(0, 0, 200, 200), QPen(Qt::black), QBrush(color));
    pRectitem->setFlags(QGraphicsItem::ItemIsMovable);
    pRectitem->setZValue(0);
}

void ShapesGraphics::addEllipse()
{
    int red = 128 + QRandomGenerator::global()->bounded(100);
    int green = 128 + QRandomGenerator::global()->bounded(100);
    int blue = 128 + QRandomGenerator::global()->bounded(100);
    QColor color = QColor(red, green, blue);

    QGraphicsEllipseItem* pElliseitem = scene->addEllipse(0,0,300,200, QPen(Qt::black), QBrush(color));
    pElliseitem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::addTriangle()
{
    int red = 128 + QRandomGenerator::global()->bounded(100);
    int green = 128 + QRandomGenerator::global()->bounded(100);
    int blue = 128 + QRandomGenerator::global()->bounded(100);
    QColor color = QColor(red, green, blue);

    QPolygon triangle;
    triangle << QPoint(0.75*200, 0)
             << QPoint(0, 200)
             << QPoint(1.5*200, 200);

    QGraphicsPolygonItem* pTriangleItem = scene->addPolygon(triangle,QPen(Qt::black), QBrush(color));
    pTriangleItem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::deleteItem()
{
    if(lastActiveItem){
        scene->removeItem(lastActiveItem);
        delete lastActiveItem;
        lastActiveItem = nullptr;
    }
}

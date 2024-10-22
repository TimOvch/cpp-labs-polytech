#ifndef SHAPESGRAPHICS_H
#define SHAPESGRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QWidget>
#include <QMouseEvent>

class ShapesGraphics : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene* scene;
    QGraphicsItem* lastActiveItem;

public:
    ShapesGraphics(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void addRect();
    void addEllipse();
    void addTriangle();

    void deleteItem();
};

#endif // SHAPESGRAPHICS_H

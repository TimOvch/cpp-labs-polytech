#ifndef SHAPESWINDOW_H
#define SHAPESWINDOW_H

#include <QWidget>
#include "rect.h"
#include "shape.h"
#include "ellipse.h"
#include "triangle.h"
#include <QVector>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ShapesWindow : public QWidget
{
    Q_OBJECT

    QVector<Shape*> shapes;
    Shape* activeShape;
public:
    explicit ShapesWindow(QWidget *parent = nullptr);

public slots:
    void Activated(Shape*act);
    void DeleteActiveShape();

    void addRect();
    void addEllipse();
    void addTriangle();

signals:
};

#endif // SHAPESWINDOW_H

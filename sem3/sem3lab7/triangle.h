#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

#define TRIANGLE_SIZE 200

class Triangle : public Shape
{
    Q_OBJECT
public:
    explicit Triangle(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev) override;

signals:
};

#endif // TRIANGLE_H

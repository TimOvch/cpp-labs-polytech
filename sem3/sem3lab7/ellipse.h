#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QWidget>
#include "shape.h"

#define ELLIPSE_X_SIZE 300
#define ELLIPSE_Y_SIZE 200

class Ellipse : public Shape
{
    Q_OBJECT
public:
    explicit Ellipse(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev) override;

signals:
};

#endif // ELLIPSE_H

#ifndef RECT_H
#define RECT_H

#include "shape.h"

#define RECT_SIZE 200

class Rect : public Shape
{
    Q_OBJECT

public:
    explicit Rect(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev) override;

signals:
};

#endif // RECT_H

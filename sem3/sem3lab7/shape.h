#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <QColor>

#define BRUSH_NON_ACTIVE 2
#define BRUSH_ACTIVE 5

class Shape : public QWidget
{
    Q_OBJECT

    QPoint lastMousePosition;

protected:
    bool dragging;
    QColor color;

public:
    explicit Shape(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void Activated(Shape*);
};

#endif // SHAPE_H

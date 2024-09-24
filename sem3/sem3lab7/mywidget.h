#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVector>
#include <QRegion>

class MyWidget : public QWidget
{
    Q_OBJECT

    QVector<QRegion*> regions;
    bool isDragging;
    int index;
    QPoint offset;

public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
};

#endif // MYWIDGET_H

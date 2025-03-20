#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVector>
#include <QPointF>
#include <QMouseEvent>

class GraphView : public QWidget {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);

    void setAdjacencyMatrix(const QVector<QVector<int>> &matrix, bool isDirected);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QPointF> nodes;
    bool directed;
    int selectedNode = -1;
};

#endif // GRAPHVIEW_H

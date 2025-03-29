#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVector>
#include <QPointF>
#include <QMouseEvent>
#include <QTimer>
#include <QStack>
#include <QMessageBox>
#include <QPair>

class GraphView : public QWidget {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);

    void setAdjacencyMatrix(const QVector<QVector<int>> &matrix, bool isDirected);
    void setWeightsMatrix(const QVector<QVector<int>> &matrix);
    void setCapacitiesMatrix(const QVector<QVector<int>> &matrix);
    void highlightPath(const QVector<int>& path);
    void clearHighlightedPath();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QVector<int>> weightsMatrix;
    QVector<QVector<int>> capacitiesMatrix;
    QVector<QPointF> nodes;
    QVector<int> highlightedPath;
    bool directed;
    bool flow;
    int selectedNode = -1;
};

#endif // GRAPHVIEW_H

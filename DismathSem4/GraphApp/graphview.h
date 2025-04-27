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
#include <QWheelEvent>
#include <QQueue>

class GraphView : public QWidget {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);

    void setAdjacencyMatrix(const QVector<QVector<int>> &matrix, bool isDirected);
    void setWeightsMatrix(const QVector<QVector<int>> &matrix);
    void setCapacitiesMatrix(const QVector<QVector<int>> &matrix);
    void setCostsMatrix(const QVector<QVector<int>> &matrix);
    void setParametrs(const bool &showWts, const bool &showCaps, const bool &showCts);
    void highlightPath(const QVector<int>& path);
    void clearHighlightedPath();
    void setTreeFromPrufer(const QVector<int>& pruferCode, const QVector<int>& edgeWeights);
    void setEdgesSets(const QVector<QPair<int,int>>& graphHigh, const QVector<QPair<int,int>>& treeHigh);
    void setEdgesHighlight(const bool& high);
    void highlightEdges(QPair<QVector<QPair<int,int>>,QVector<QPair<int,int>>> addAndDel);
    void setCycleEdgesHighlight(const bool& tmp);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private:
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QVector<int>> weightsMatrix;
    QVector<QVector<int>> capacitiesMatrix;
    QVector<QVector<int>> costsMatrix;
    QVector<QPair<int,int>> edgesToHighlightGraph;
    QVector<QPair<int,int>> edgesToHighlightTree;
    QVector<QPointF> nodes;
    bool isTree;
    QVector<QPair<int, int>> treeEdges;
    QVector<int> treeWeights;
    QVector<int> highlightedPath;
    QVector<QPair<int,int>> added;
    QVector<QPair<int,int>> deleted;
    bool directed;
    bool flow;
    bool showWeights;
    bool showCapacities;
    bool showCosts;
    bool showSets;
    bool showHighlightEdges;
    int selectedNode = -1;
    double scaleFactor = 1.0;
};

#endif // GRAPHVIEW_H

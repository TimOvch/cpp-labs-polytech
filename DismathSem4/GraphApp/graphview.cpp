#include "graphview.h"



GraphView::GraphView(QWidget *parent) : QWidget(parent), directed(false), flow(0), showWeights(1), showCapacities(1), showCosts(1), isTree(0), showHighlightEdges(1) {
}

void GraphView::setAdjacencyMatrix(const QVector<QVector<int> > &matrix, bool isDirected) {
    isTree = 0;
    adjacencyMatrix = matrix;
    directed = isDirected;
    flow = 0;
    highlightedPath.clear();
    added.clear();
    deleted.clear();

    nodes.clear();
    int n = matrix.size();
    if (n == 0) return;

    int radius = 250;
    QPointF center(width() / 2.0, height() / 2.0);
    double angleStep = 2 * M_PI / n;

    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        QPointF nodePos = center + QPointF(radius * cos(angle), radius * sin(angle));
        nodes.append(nodePos);
    }

    update();
}

void GraphView::setWeightsMatrix(const QVector<QVector<int>> &matrix)
{
    weightsMatrix = matrix;
}

void GraphView::setCapacitiesMatrix(const QVector<QVector<int> > &matrix) {
    capacitiesMatrix = matrix;
    flow = 1;
}

void GraphView::setCostsMatrix(const QVector<QVector<int> > &matrix)
{
    costsMatrix = matrix;
}

void GraphView::setParametrs(const bool &showWts, const bool &showCaps, const bool &showCts)
{
    showWeights = showWts;
    showCapacities = showCaps;
    showCosts = showCts;
    update();
}

void GraphView::highlightPath(const QVector<int> &path) {
    highlightedPath = path;
    update();
}

void GraphView::clearHighlightedPath() {
    highlightedPath.clear();
    update();
}

void GraphView::setTreeFromPrufer(const QVector<int> &pruferCode, const QVector<int> &edgeWeights) {
    int n = pruferCode.size() + 1;
    treeEdges.clear();
    treeWeights.clear();
    nodes.clear();

    if (pruferCode.isEmpty() || edgeWeights.isEmpty() || edgeWeights.size() != pruferCode.size()) {
        qDebug() << "Invalid input for tree construction";
        return;
    }

    QVector<int> degree(n + 1, 1);
    for (int i = 0; i < pruferCode.size(); ++i) {
        degree[pruferCode[i]]++;
    }

    QVector<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            leaves.push_back(i);
        }
    }

    for (int i = 0; i < pruferCode.size(); ++i) {
        int leaf = leaves.front();
        leaves.pop_front();

        int parent = pruferCode[i];
        treeEdges.append(qMakePair(leaf, parent));

        if (i < edgeWeights.size()) {
            treeWeights.append(edgeWeights[i]);
        } else {
            treeWeights.append(1);
        }

        degree[parent]--;
        if (degree[parent] == 1) {
            leaves.push_back(parent);
        }

        if (i == pruferCode.size() - 1) {
            treeEdges.append(qMakePair(leaves.front(), leaves.back()));
            treeWeights.append(edgeWeights.last());
        }
    }

    int radius = qMin(width(), height()) / 3;
    QPointF center(width() / 2.0, height() / 2.0);
    double angleStep = 2 * M_PI / n;

    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        nodes.append(center + QPointF(radius * cos(angle), radius * sin(angle)));
    }

    isTree = true;
    directed = false;
    flow = false;

    update();
}

void GraphView::setEdgesSets(const QVector<QPair<int,int>>& graphHigh, const QVector<QPair<int,int>>& treeHigh)
{
    edgesToHighlightGraph = graphHigh;
    edgesToHighlightTree = treeHigh;
    update();
}

void GraphView::setEdgesHighlight(const bool &high)
{
    showSets = high;
    update();
}

void GraphView::highlightEdges(QPair<QVector<QPair<int,int>>,QVector<QPair<int,int>>> addAndDel)
{
    added = addAndDel.first;
    deleted = addAndDel.second;
}

void GraphView::setCycleEdgesHighlight(const bool &tmp){
    showHighlightEdges = tmp;
    update();
}

void GraphView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(scaleFactor, scaleFactor);

    if (adjacencyMatrix.isEmpty() && !isTree) {
        painter.drawText(rect(), Qt::AlignCenter, "Визуализация отсутствует: нет активного графа");
        return;
    }

    int n = adjacencyMatrix.size();
    if (n == 0 && !isTree) return;

    if (isTree) {
        painter.setPen(QPen(Qt::black));

        for (int i = 0; i < treeEdges.size(); ++i) {
            int u = treeEdges[i].first;
            int v = treeEdges[i].second;

            if (u >= nodes.size() || v >= nodes.size()) continue;

            QPointF from = nodes[u];
            QPointF to = nodes[v];
            painter.setPen(QPen(Qt::black));

            bool isHighlighted = false;
            for(int k = 0; k < edgesToHighlightTree.size(); k++){
                QPair<int,int> pair = edgesToHighlightTree[k];
                if((pair.first == u && pair.second == v) || (pair.first == v && pair.second == u)){
                    isHighlighted = true;
                    break;
                }
            }

            if(isHighlighted && showSets){
                painter.setPen(QPen(Qt::red, 3));
            }

            painter.drawLine(from, to);

            painter.setPen(QPen(Qt::black));

            if (i < treeWeights.size()) {
                QPointF midPoint = (from + to) / 2.0;
                QString weightLabel = QString::number(treeWeights[i]);
                QRectF weightRect(midPoint.x() - 10, midPoint.y() - 10, 30, 20);
                painter.setBrush(QColor(255, 255, 255, 150));
                painter.setPen(Qt::NoPen);

                painter.drawRoundedRect(weightRect, 5, 5);

                if (treeWeights[i] < 0) {
                    painter.setPen(Qt::red);
                } else {
                    painter.setPen(Qt::blue);
                }

                painter.drawText(weightRect, Qt::AlignCenter, weightLabel);
            }
        }

        painter.setPen(QPen(Qt::black));

        for (int i = 0; i < nodes.size(); ++i) {
            QPointF nodePos = nodes[i];
            painter.setBrush(Qt::lightGray);
            painter.drawEllipse(nodePos, 20, 20);

            QString nodeLabel = QString::number(i+1);
            painter.setPen(QPen(Qt::black));
            QRectF textRect(nodePos.x() - 15, nodePos.y() - 10, 30, 20);
            painter.drawText(textRect, Qt::AlignCenter, nodeLabel);
        }

        return;
    }

    QPen pen(Qt::black);
    painter.setPen(pen);

    for (int i = 0; i < n; ++i) {
        QPointF nodePos = nodes[i];
        painter.setBrush(Qt::lightGray);
        painter.drawEllipse(nodePos, 20, 20);
        QString nodeLabel = QString::number(i + 1);
        QRectF textRect(nodePos.x() - 15, nodePos.y() - 10, 30, 20);
        painter.drawText(textRect, Qt::AlignCenter, nodeLabel);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                QPointF from = nodes[i];
                QPointF to = nodes[j];
                double angle = atan2(to.y() - from.y(), to.x() - from.x());
                QPointF adjustedFrom = from + QPointF(20 * cos(angle), 20 * sin(angle));
                QPointF adjustedTo = to - QPointF(20 * cos(angle), 20 * sin(angle));

                bool isHighlighted = false;
                for (int k = 0; k < highlightedPath.size() - 1; ++k) {
                    if ((highlightedPath[k] == i && highlightedPath[k + 1] == j) ||
                        (!directed && highlightedPath[k] == j && highlightedPath[k + 1] == i)) {
                        isHighlighted = true;
                        break;
                    }
                }

                bool isHighlighted2 = false;
                for(int k = 0; k < edgesToHighlightGraph.size(); k++){
                    QPair<int,int> pair = edgesToHighlightGraph[k];
                    if((pair.first == i && pair.second == j) || (pair.first == j && pair.second == i)){
                        isHighlighted2 = true;
                        break;
                    }
                }

                bool isHighlighted3 = false;

                for(int k = 0; k < added.size(); k++){
                    if((i == added[k].first && j == added[k].second) ||
                        (i == added[k].second && j == added[k].first)){
                        isHighlighted3 = true;
                        break;
                        }
                }

                if (isHighlighted || (isHighlighted2 && showSets)) {
                    painter.setPen(QPen(Qt::red, 3));
                } else if(isHighlighted3&&showHighlightEdges){
                    painter.setPen(QPen(Qt::green, 2));
                } else {
                    painter.setPen(QPen(Qt::black, 1));
                }

                painter.drawLine(adjustedFrom, adjustedTo);

                if (directed) {
                    QPointF arrowP1 = adjustedTo - QPointF(10 * cos(angle + M_PI / 6), 10 * sin(angle + M_PI / 6));
                    QPointF arrowP2 = adjustedTo - QPointF(10 * cos(angle - M_PI / 6), 10 * sin(angle - M_PI / 6));
                    painter.drawLine(adjustedTo, arrowP1);
                    painter.drawLine(adjustedTo, arrowP2);
                }

                QPointF midPoint = (adjustedFrom + adjustedTo) / 2;
                if(showWeights){
                    QString weightLabel = QString::number(weightsMatrix[i][j]);
                    QRectF weightRect(midPoint.x() - 15, midPoint.y() - 15, 30, 20);
                    painter.setBrush(QColor(255, 255, 255, 150));
                    painter.setPen(Qt::NoPen);
                    painter.drawRoundedRect(weightRect, 5, 5);

                    if (weightsMatrix[i][j] < 0) {
                        painter.setPen(Qt::red);
                    } else {
                        painter.setPen(Qt::blue);
                    }

                    painter.drawText(weightRect, Qt::AlignCenter, weightLabel);
                }

                if(flow){
                    if(showCapacities){
                        QString capacityLabel = QString::number(capacitiesMatrix[i][j]);
                        if(capacitiesMatrix[i][j] == INT_MAX){
                            capacityLabel = "\u221E";
                        }
                        QRectF capacityRect(midPoint.x(), midPoint.y() + 20, 30, 20);
                        painter.setBrush(QColor(255, 255, 255, 150));
                        painter.setPen(Qt::NoPen);
                        painter.drawRoundedRect(capacityRect, 5, 5);
                        painter.setPen(Qt::darkGreen);
                        painter.drawText(capacityRect, Qt::AlignCenter, capacityLabel);
                    }

                    if(showCosts){
                        QString capacityLabel = QString::number(costsMatrix[i][j]);
                        if(costsMatrix[i][j] == INT_MAX){
                            capacityLabel = "\u221E";
                        }
                        QRectF capacityRect(midPoint.x() - 30, midPoint.y(), 30, 20);
                        painter.setBrush(QColor(255, 255, 255, 150));
                        painter.setPen(Qt::NoPen);
                        painter.drawRoundedRect(capacityRect, 5, 5);
                        painter.setPen(Qt::darkYellow);
                        painter.drawText(capacityRect, Qt::AlignCenter, capacityLabel);
                    }
                }

                painter.setPen(Qt::black);
            }
        }
    }

    if(showHighlightEdges){
        for(int k = 0; k < deleted.size(); k++){
            QPen pen(Qt::red, 1);
            pen.setStyle(Qt::DotLine);
            painter.setPen(pen);

            QPointF from = nodes[deleted[k].first];
            QPointF to = nodes[deleted[k].second];
            double angle = atan2(to.y() - from.y(), to.x() - from.x());
            QPointF adjustedFrom = from + QPointF(20 * cos(angle), 20 * sin(angle));
            QPointF adjustedTo = to - QPointF(20 * cos(angle), 20 * sin(angle));
            painter.drawLine(adjustedFrom, adjustedTo);
        }
    }
}

void GraphView::mousePressEvent(QMouseEvent *event) {
    QPointF mousePos = event->pos();
    for (int i = 0; i < nodes.size(); ++i) {
        if (QLineF(mousePos, nodes[i]).length() <= 20) {
            selectedNode = i;
            qDebug() << "Selected node:" << selectedNode;
            break;
        }
    }
}

void GraphView::mouseMoveEvent(QMouseEvent *event) {
    if (selectedNode != -1) {
        nodes[selectedNode] = event->pos();
        qDebug() << "Moving node:" << selectedNode << "to" << event->pos();
        repaint();
    }
}

void GraphView::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    qDebug() << "Released node:" << selectedNode;
    selectedNode = -1;
}

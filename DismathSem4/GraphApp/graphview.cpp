#include "graphview.h"



GraphView::GraphView(QWidget *parent) : QWidget(parent), directed(false) {}

void GraphView::setAdjacencyMatrix(const QVector<QVector<int> > &matrix, bool isDirected) {
    adjacencyMatrix = matrix;
    directed = isDirected;


    nodes.clear();
    int n = matrix.size();
    if (n == 0) return;

    int radius = 150;
    QPointF center(width() / 2.0, height() / 2.0);
    double angleStep = 2 * M_PI / n;

    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        QPointF nodePos = center + QPointF(radius * cos(angle), radius * sin(angle));
        nodes.append(nodePos);
    }

    update();
}

void GraphView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (adjacencyMatrix.isEmpty()) {
        painter.drawText(rect(), Qt::AlignCenter, "Визуализация отсутсвует: нет активного графа");
        return;
    }

    int n = adjacencyMatrix.size();
    if (n == 0) return;

    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    for (int i = 0; i < n; ++i) {
        QPointF nodePos = nodes[i];
        painter.setBrush(Qt::lightGray);
        painter.drawEllipse(nodePos, 20, 20);

        QString nodeLabel = QString::number(i+1);
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

                painter.drawLine(adjustedFrom, adjustedTo);

                if (directed) {
                    QPointF arrowP1 = adjustedTo - QPointF(10 * cos(angle + M_PI / 6), 10 * sin(angle + M_PI / 6));
                    QPointF arrowP2 = adjustedTo - QPointF(10 * cos(angle - M_PI / 6), 10 * sin(angle - M_PI / 6));
                    painter.drawLine(adjustedTo, arrowP1);
                    painter.drawLine(adjustedTo, arrowP2);
                }
            }
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

#ifndef SHAPESGRAPHICS_H
#define SHAPESGRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QVector>
#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QHash>
#include <QPointF>

class ConnectionLine : public QGraphicsLineItem {
public:
    ConnectionLine(QGraphicsItem* item1, QGraphicsItem* item2);

    void updateLine();
    bool contains(QGraphicsItem* item);

private:
    QGraphicsItem* item1;
    QGraphicsItem* item2;
};

class ShapesGraphics : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene* scene;
    QGraphicsItem* lastActiveItem;
    QHash<int, QGraphicsItem*> idToItem;
    QHash<QGraphicsItem*, int> itemToId;
    QHash<QGraphicsItem*, QColor> itemToColor;
    QVector<ConnectionLine*> lines;
    bool mouseHold;

public:
    ShapesGraphics(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void addShape(QGraphicsItem* shape, const int& id);

public slots:
    void addRect(const int& id, const QColor& color, const int& x = 0, const int& y = 0);
    void addEllipse(const int& id, const QColor& color, const int& x = 0, const int& y = 0);
    void addTriangle(const int& id, const QColor& color, const int& x = 0, const int& y = 0);

    void addRelation(const int& id1, const int& id2);
    void deleteRelation(const int& id1, const int& id2);

    void deleteItem(const int& id);
    void hideItemFilter(const int& id);
    void showAll();

    void markItem(const int& id);
    void unMarkAll();

signals:
    void posChangedIk(const int& id, const int& x, const int &y);
    void selectFig(const int &x , const int &y);
};

#endif // SHAPESGRAPHICS_H


#include "shapesgraphics.h"
#include "QGraphicsRectItem"
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QHBoxLayout>
#include <QPushButton>
#include "QRandomGenerator"
#include <QColor>
#include <QMessageBox>
#include <QPointF>
#include <QRectF>
#include <QMetaClassInfo>

QPointF getCenter(QGraphicsItem *item) {
    if (item) {
        QRectF boundingRect = item->boundingRect();
        return QPointF(boundingRect.center() + item->pos());
    }
    return QPointF();
}

ShapesGraphics::ShapesGraphics(QWidget* parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mouseHold = 0;
}

void ShapesGraphics::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastActiveItem = scene->itemAt(mapToScene(event->pos()), QTransform());
        if (lastActiveItem) {
            QPointF pos = lastActiveItem->pos();
            scene->removeItem(lastActiveItem);
            scene->addItem(lastActiveItem);
            lastActiveItem->setPos(pos);
            mouseHold = 1;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void ShapesGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    lastActiveItem = scene->itemAt(mapToScene(event->pos()), QTransform());
    if(lastActiveItem != nullptr){
        emit posChanged(itemToId[lastActiveItem], lastActiveItem->scenePos().x(), lastActiveItem->scenePos().y());
    }
    mouseHold = 0;
    QGraphicsView::mouseReleaseEvent(event);
}

void ShapesGraphics::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);

    if(mouseHold){
        for(int i = 0; i < lines.length(); i++){
            if(lines[i]->contains(lastActiveItem)){
                lines[i]->updateLine();
            }
        }
    }
}

void ShapesGraphics::addShape(QGraphicsItem *shape, const int& id)
{
    scene->addItem(shape);
    idToItem[id] = shape;
    itemToId[shape] = id;
}

void ShapesGraphics::addRect(const int& id, const QColor& color, const int& x, const int& y)
{
    QGraphicsRectItem* pRectitem = scene->addRect(QRectF(x, y, 100, 100), QPen(Qt::black), QBrush(color));

    itemToColor[pRectitem] = color;

    idToItem[id] = pRectitem;
    itemToId[pRectitem] = id;
    pRectitem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::addEllipse(const int& id, const QColor& color, const int& x, const int& y)
{
    QGraphicsEllipseItem* pElliseitem = scene->addEllipse(x,y,100,100, QPen(Qt::black), QBrush(color));

    itemToColor[pElliseitem] = color;

    idToItem[id] = pElliseitem;
    itemToId[pElliseitem] = id;
    pElliseitem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::addTriangle(const int& id, const QColor& color, const int& x, const int& y)
{
    QPolygon triangle;
    triangle << QPoint(x+0.75*100, y)
             << QPoint(x, y+100)
             << QPoint(x+1.5*100,y+ 100);

    QGraphicsPolygonItem* pTriangleItem = scene->addPolygon(triangle,QPen(Qt::black), QBrush(color));

    itemToColor[pTriangleItem] = color;

    idToItem[id] = pTriangleItem;
    itemToId[pTriangleItem] = id;
    pTriangleItem->setFlags(QGraphicsItem::ItemIsMovable);
}

void ShapesGraphics::addRelation(const int &id1, const int &id2)
{
    QGraphicsItem* it1 = idToItem.value(id1, nullptr);
    QGraphicsItem* it2 = idToItem.value(id2, nullptr);

    for(int i = 0; i < lines.length(); i++){
        if(lines[i]->contains(it1) && lines[i]->contains(it2)){
            scene->removeItem(lines[i]);
            delete lines[i];
            lines.removeAt(i);
        }
    }

    ConnectionLine* line = new ConnectionLine(it1,it2);
    line->setZValue(-1);
    scene->addItem(line);
    lines.push_back(line);
}

void ShapesGraphics::deleteRelation(const int &id1, const int &id2)
{
    for(int i = 0; i < lines.length(); i++){
        if(lines[i]->contains(idToItem[id1]) && lines[i]->contains(idToItem[id2])){
            scene->removeItem(lines[i]);
            delete lines[i];
            lines.removeAt(i);
        }
    }

    qDebug() << lines.length();
}

void ShapesGraphics::deleteItem(const int& id)
{
    if (idToItem.contains(id)) {
        QGraphicsItem* item = idToItem[id];
        itemToId.remove(item);
        idToItem.remove(id);

        for (int i = lines.length() - 1; i >= 0; --i) {
            if (lines[i]->contains(item)) {
                scene->removeItem(lines[i]);
                delete lines[i];
                lines.removeAt(i);
            }
        }

        scene->removeItem(item);
        delete item;
    }
}

void ShapesGraphics::hideItemFilter(const int &id)
{
    idToItem[id]->setVisible(false);

    for(int i = 0; i < lines.length(); i++){
        if(lines[i]->contains(idToItem[id])){
            lines[i]->setVisible(false);
        }
    }
}

void ShapesGraphics::showAll()
{
    QList<QGraphicsItem *> items = scene->items();

    for (QGraphicsItem *item : items) {
        item->setVisible(true);
    }

    for(int i = 0; i < lines.length(); i++){
        lines[i]->setVisible(true);
    }
}

void ShapesGraphics::markItem(const int &id)
{
    QGraphicsItem* item = idToItem[id];

    if (dynamic_cast<QGraphicsRectItem*>(item)) {
        QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item);
        rect->setBrush(QBrush(Qt::red));
    } else if (dynamic_cast<QGraphicsEllipseItem*>(item)) {
        QGraphicsEllipseItem* ellipse = dynamic_cast<QGraphicsEllipseItem*>(item);
        ellipse->setBrush(QBrush(Qt::red));
    } else if (dynamic_cast<QGraphicsPolygonItem*>(item)) {
        QGraphicsPolygonItem* triangle = dynamic_cast<QGraphicsPolygonItem*>(item);
        triangle->setBrush(QBrush(Qt::red));
    }

}

void ShapesGraphics::unMarkAll()
{
    QList<QGraphicsItem *> items = scene->items();

    for (QGraphicsItem *item : items) {
        if (dynamic_cast<QGraphicsRectItem*>(item)) {
            QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item);
            rect->setBrush(QBrush(itemToColor[item]));
        } else if (dynamic_cast<QGraphicsEllipseItem*>(item)) {
            QGraphicsEllipseItem* ellipse = dynamic_cast<QGraphicsEllipseItem*>(item);
            ellipse->setBrush(QBrush(itemToColor[item]));
        } else if (dynamic_cast<QGraphicsPolygonItem*>(item)) {
            QGraphicsPolygonItem* triangle = dynamic_cast<QGraphicsPolygonItem*>(item);
            triangle->setBrush(QBrush(itemToColor[item]));
        }
    }
}

ConnectionLine::ConnectionLine(QGraphicsItem *item1, QGraphicsItem *item2)
    : QGraphicsLineItem(), item1(item1), item2(item2) {
    setPen(QPen(Qt::white));
    updateLine();
}

void ConnectionLine::updateLine() {
    if (item1 && item2) {
        QPointF center1 = item1->boundingRect().center() + item1->pos();
        QPointF center2 = item2->boundingRect().center() + item2->pos();
        setLine(QLineF(center1, center2));
    }
}

bool ConnectionLine::contains(QGraphicsItem *item){
    return (item1 == item) || (item2 == item);
}

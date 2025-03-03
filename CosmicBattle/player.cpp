#include "player.h"
#include <QKeyEvent>
#include <QDebug>

Player::Player(QGraphicsItem* parent): QGraphicsPixmapItem(parent)
{
    QPixmap image(":/images/Player1.png");


    setPixmap(image.scaled(250,250));

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
            setPos(x()+10,y());
    }

    qDebug() << x() << " " << y();
}

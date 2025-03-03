#include "game.h"

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    setScene(scene);


    player = new Player;
    player->setPos(400,500);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    show();
}

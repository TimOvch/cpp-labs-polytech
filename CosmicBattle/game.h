#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <QGraphicsView>

class Game : public QGraphicsView
{
    Player* player;
    QGraphicsScene* scene;
public:
    Game(QWidget* parent);
};

#endif // GAME_H

//
// Created by Тимофей Овчинников on 03.05.2024.
//

#include <iostream>
#include "player.h"

#ifndef TICTACTOE_PYTHONPLAYER_H
#define TICTACTOE_PYTHONPLAYER_H


class PythonPlayer : public Player{
public:
    PythonPlayer() = default;
    std::string get_name() const override { return {"PythonPlayer"};}
    Point play(const GameView& game) override;
    void assign_mark(Mark player_mark) override { /*does nothing*/ }
    void notify(const GameView&, const Event&) override { /*does nothing*/ }
};


#endif //TICTACTOE_PYTHONPLAYER_H

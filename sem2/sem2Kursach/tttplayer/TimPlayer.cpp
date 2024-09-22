//
// Created by Тимофей Овчинников on 29.04.2024.
//
#pragma once
#include "TimPlayer.h"
#include <iostream>

namespace ovchinnikov_2 {
    Player* makePlayer(){
        return new TimPlayer;
    }

    TimPlayer::TimPlayer() {
        myMark = Mark::None;
        prevStatus = Attack;
    }

    std::string TimPlayer::get_name() const {
        std::string name{"Timophey"};
        return name;
    }

    Point TimPlayer::play(const GameView &game) {
        Analyzer analyzer(prevStatus, myMark, 2);
        analyzer.analyze(game);
        Point decision = analyzer.decision();
        prevStatus = analyzer.next_prev_status();

        return decision;
    }

    void TimPlayer::assign_mark(Mark player_mark) {
        myMark = player_mark;
    }
}
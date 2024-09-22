#pragma once
#include <ostream>
#include "player.h"
#include "Analyzer.h"

namespace ovchinnikov_2 {
    Player* makePlayer();

    class TimPlayer : public Player {
        Mark myMark;
        Status prevStatus;
    public:
        TimPlayer();

        std::string get_name() const override;

        Point play(const GameView &game) override;

        void assign_mark(Mark player_mark) override;

        void notify(const GameView &, const Event &) override {}
    };
}
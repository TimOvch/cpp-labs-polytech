/**
 *  This is example of game, that you can use for debugging.
 */
#include <cstdlib>
#include <ctime>
#include <iostream>


#include "my_player.h"
#include "TimPlayer.h"
#include "game_engine.h"
#include "PythonPlayer.h"

void Test(){
    GameSettings settings = {
            .field_size = {
                    .min = {.x = 0, .y = 0},
                    .max = {.x = 40, .y = 40},
            },
            .max_moves = 1000,
            .win_length = 5,
            .move_timelimit_ms = 0,
    };

    GameEngine game1(settings), game2(settings);

    ovchinnikov_2::TimPlayer player1;
    RandomPlayer player2("Рандом");
    game1.set_player(player1);
    game1.set_player(player2);

    game2.set_player(player2);
    game2.set_player(player1);
    int WinsCounter = 0;

    for(int i = 0; i < 1; i++){
        Mark winner1 = game1.play_game();
        Mark winner2 = game2.play_game();

        if(winner1 == Mark::Cross){
            WinsCounter++;
        }
        if(winner2 == Mark::Zero){
            WinsCounter++;
        }
    }
    double percent = WinsCounter/2000 * 100;

    std::cout << "TimPlayer's win percent: " << percent << "%";

}


/*
 *
 *
 */

int main() {
    //Test();
    srand(time(0));
    GameSettings settings = {
            .field_size = {
                    .min = {.x = 0, .y = 0},
                    .max = {.x = 20, .y = 20},
            },
            .max_moves = 1000,
            .win_length = 5,
            .move_timelimit_ms = 0,
    };

    GameEngine game2(settings);
    BasicObserver observer(std::cout);
    game2.get_view().add_observer(observer);

    ovchinnikov_2::TimPlayer player1;
    Mihali::MyPlayer player2("Putyata");

    game2.set_player(player1);
    game2.set_player(player2);

    Mark winner2 = game2.play_game();

    return 0;
}

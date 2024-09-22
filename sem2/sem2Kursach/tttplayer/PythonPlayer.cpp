//
// Created by Тимофей Овчинников on 03.05.2024.
//

#include "PythonPlayer.h"
#include <iostream>
#include <string>

Point PythonPlayer::play(const GameView& game){
    int x, y;
    std::string cop,x_str,y_str;
    std::cin >> cop;
    std::cin >> x_str;
    std::cin >> y_str;

    x = stoi(x_str);
    y = stoi(y_str);

    return Point{x,y};
}
#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>

class Move {
public:
    int moveNumber;
    char player;
    std::string position;

    Move(int number, char player, const std::string& pos);

    static Move parseMove(const std::string& moveStr);
    bool isValid() const;
};

#endif

#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>

class Move {
public:
    int moveNumber;
    char player;
    char row;
    int column;
    std::string comment;

    Move();
    Move(int moveNumber, char player, char row, int column, std::string comment = "");

    friend std::istream& operator>>(std::istream& is, Move& move);
    friend std::ostream& operator<<(std::ostream& os, const Move& move);

    bool isValid() const;
};

#endif

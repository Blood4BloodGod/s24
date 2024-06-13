#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include <vector>
#include <string>

class Board {
public:
    Board();
    bool applyMove(const Move& move);
    std::string evaluate() const;

private:
    std::vector<std::vector<char>> board;
    int moveCount;
    bool isWin(char player) const;
    bool isFull() const;
};

#endif

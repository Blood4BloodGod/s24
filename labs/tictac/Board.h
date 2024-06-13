#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Move.h"

class Board {
private:
    std::vector<std::vector<char>> grid;
    bool isValid;
    int moveCount;
    char lastPlayer;
    bool gameEnded; // Add this flag

public:
    Board();
    bool addMove(const Move& move);
    std::string checkGameState() const;
    void printBoard() const;
};

#endif // BOARD_H

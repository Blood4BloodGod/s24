#include "Board.h"
#include <iostream>
#include <sstream>

int main() {
    Board board;
    std::string line;
    int expectedMoveNumber = 1;
    char currentPlayer = 'X';

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        Move move;
        if (!(iss >> move) || !move.isValid() || move.moveNumber != expectedMoveNumber || move.player != currentPlayer) {
            std::cout << "Invalid move: " << line << std::endl;
            return 1;
        }

        if (!board.applyMove(move)) {
            std::cout << "Invalid move: " << line << std::endl;
            return 1;
        }

        expectedMoveNumber++;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    std::cout << board.evaluate() << std::endl;
    return 0;
}

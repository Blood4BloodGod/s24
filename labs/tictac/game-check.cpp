#include "Board.h"
#include "Move.h"
#include <iostream>
#include <string>

int main() {
    Board board;
    std::string line;
    int moveCount = 0;

    while (std::getline(std::cin, line)) {
        Move move = Move::parseMove(line);
        if (!move.isValid() || !board.addMove(move)) {
            std::cout << "Invalid move." << std::endl;
            return 1;
        }
        moveCount++;
    }

    std::string result = board.checkGameState();
    std::cout << result << std::endl;
    return 0;
}

#include "Board.h"
#include "Move.h"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    Board board;
    std::string line;

    try {
        while (std::getline(std::cin, line)) {
            Move move = Move::parseMove(line);
            if (!move.isValid() || !board.addMove(move)) {
                std::cout << "Invalid move." << std::endl;
                return 1;
            }
        }

        std::string result = board.checkGameState();
        std::cout << result << std::endl;
        return 0;
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid move." << std::endl;
        return 1;
    }
}

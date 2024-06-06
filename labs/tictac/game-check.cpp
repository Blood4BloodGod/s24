#include "Board.h"
#include "Move.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

int main() {
    Board board;
    std::string line;

    try {
        while (std::getline(std::cin, line)) {
            // Remove comments and normalize whitespace
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }
            line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");

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

#include "Board.h"
#include "Move.h"
#include <iostream>
#include <string>
#include <regex>

int main() {
    Board board;
    std::string line;

    try {
        int expectedMoveNumber = 1;
        char currentPlayer = 'X';

        while (std::getline(std::cin, line)) {
            // Remove comments and normalize whitespace
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }
            line = std::regex_replace(line, std::regex("\\s+"), " ");
            line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

            Move move = Move::parseMove(line);
            if (!move.isValid() || move.moveNumber != expectedMoveNumber || move.player != currentPlayer || !board.addMove(move)) {
                std::cout << "Invalid move." << std::endl;
                return 2;
            }

            expectedMoveNumber++;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        std::string result = board.checkGameState();
        std::cout << result << std::endl;
        return 0;
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid move." << std::endl;
        return 2;
    }
}

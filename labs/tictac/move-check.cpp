#include "Move.h"
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string line;
    std::getline(std::cin, line);

    try {
        Move move = Move::parseMove(line);
        if (move.isValid()) {
            std::cout << move << std::endl;
            return 0;
        } else {
            std::cout << "Parse error." << std::endl;
            return 1;
        }
    } catch (const std::invalid_argument&) {
        std::cout << "Parse error." << std::endl;
        return 1;
    }
}


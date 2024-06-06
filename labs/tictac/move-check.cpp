#include "Move.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

int main() {
    std::string line;
    std::getline(std::cin, line);

    // Remove comments and normalize whitespace
    size_t commentPos = line.find('#');
    if (commentPos != std::string::npos) {
        line = line.substr(0, commentPos);
    }
    line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");

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

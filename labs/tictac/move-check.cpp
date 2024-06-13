#include "Move.h"
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string line;
    try {
        while (std::getline(std::cin, line)) {
            // Remove comments and normalize whitespace
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }
            line = std::regex_replace(line, std::regex("\\s+"), " ");
            line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

            Move move = Move::parseMove(line);
            if (!move.isValid()) {
                std::cout << "Parse error." << std::endl;
                return 1;
            }

            std::cout << move << std::endl;
        }
        return 0;
    } catch (const std::invalid_argument&) {
        std::cout << "Parse error." << std::endl;
        return 1;
    }
}

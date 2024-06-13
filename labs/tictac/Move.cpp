#include "Move.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

Move::Move(int number, char player, const std::string& pos)
    : moveNumber(number), player(toupper(player)), position(pos) {
    std::transform(this->position.begin(), this->position.end(), this->position.begin(), ::toupper);
}

Move Move::parseMove(const std::string& moveStr) {
    std::string cleanedStr = moveStr;
    // Remove comments
    size_t commentPos = cleanedStr.find('#');
    if (commentPos != std::string::npos) {
        cleanedStr = cleanedStr.substr(0, commentPos);
    }

    // Normalize whitespace
    cleanedStr = std::regex_replace(cleanedStr, std::regex("\\s+"), " ");
    cleanedStr = std::regex_replace(cleanedStr, std::regex("^\\s+|\\s+$"), "");

    std::istringstream iss(cleanedStr);
    int number;
    char player;
    std::string position;

    // Check for exact number of components
    if (!(iss >> number >> player >> position) || !iss.eof()) {
        throw std::invalid_argument("Invalid move format");
    }

    // Additional checks for invalid components
    if (number < 1 || number > 9) {
        throw std::invalid_argument("Invalid move number");
    }
    if (player != 'X' && player != 'O') {
        throw std::invalid_argument("Invalid player");
    }
    if (position.size() != 2 || position[0] < 'A' || position[0] > 'C' || position[1] < '1' || position[1] > '3') {
        throw std::invalid_argument("Invalid position");
    }

    return Move(number, player, position);
}

bool Move::isValid() const {
    if (moveNumber < 1 || moveNumber > 9) return false;
    if (player != 'X' && player != 'O') return false;
    if (position.size() != 2) return false;
    if (position[0] < 'A' || position[0] > 'C') return false;
    if (position[1] < '1' || position[1] > '3') return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.position;
    return os;
}

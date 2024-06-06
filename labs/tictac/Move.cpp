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
    if (!(iss >> number >> player >> position)) {
        throw std::invalid_argument("Invalid move format");
    }

    return Move(number, player, position);
}

bool Move::isValid() const {
    static const std::regex moveRegex(R"(^\d+\s+[XO]\s+[ABCabc][123]$)");
    std::string moveStr = std::to_string(moveNumber) + ' ' + player + ' ' + position;
    return std::regex_match(moveStr, moveRegex);
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.position;
    return os;
}
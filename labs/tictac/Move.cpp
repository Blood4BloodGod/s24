#include "Move.h"
#include <sstream>
#include <regex>
#include <algorithm>

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

    // Remove extra whitespace
    cleanedStr.erase(std::remove_if(cleanedStr.begin(), cleanedStr.end(), ::isspace), cleanedStr.end());

    // Extract move number, player, and position
    std::istringstream iss(cleanedStr);
    int number;
    char player;
    std::string position;
    iss >> number >> player >> position;

    return Move(number, player, position);
}

bool Move::isValid() const {
    static const std::regex moveRegex(R"(^\d+\s*[XO]\s*[ABCabc][123]$)");
    std::string moveStr = std::to_string(moveNumber) + player + position;
    return std::regex_match(moveStr, moveRegex);
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.position;
    return os;
}

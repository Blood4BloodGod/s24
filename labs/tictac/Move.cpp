#include "Move.h"
#include <sstream>
#include <regex>
#include <algorithm>

Move::Move(int number, char player, const std::string& pos)
    : moveNumber(number), player(toupper(player)), position(pos) {
    std::transform(this->position.begin(), this->position.end(), this->position.begin(), ::toupper);
}

Move Move::parseMove(const std::string& moveStr) {
    std::istringstream iss(moveStr);
    int number;
    char player;
    std::string position;
    
    // Extract move number, player, and position
    iss >> number >> player >> position;

    // Validate and parse comment if exists
    std::string comment;
    std::getline(iss, comment);
    if (!comment.empty() && comment[0] != '#') {
        throw std::invalid_argument("Invalid comment format");
    }

    return Move(number, player, position);
}

bool Move::isValid() const {
    static const std::regex moveRegex(R"(^\d+ [XO] [ABC][123]$)");
    std::string moveStr = std::to_string(moveNumber) + " " + player + " " + position;
    return std::regex_match(moveStr, moveRegex);
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.position;
    return os;
}
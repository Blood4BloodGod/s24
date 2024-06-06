#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.
#include "Move.h"
#include <sstream>
#include <regex>

Move::Move(int number, char player, const std::string& pos)
    : moveNumber(number), player(player), position(pos) {}

Move Move::parseMove(const std::string& moveStr) {
    std::istringstream iss(moveStr);
    int number;
    char player;
    std::string position;

    iss >> number >> player >> position;
    return Move(number, player, position);
}

bool Move::isValid() const {
    static const std::regex moveRegex(R"(^\d+ [XO] [ABC][123]$)");
    return std::regex_match(std::to_string(moveNumber) + " " + player + " " + position, moveRegex);
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.position;
    return os;
}
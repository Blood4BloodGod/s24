#include "Move.h"
#include <sstream>
#include <cctype>
#include <regex>

Move::Move() : moveNumber(0), player(' '), row(' '), column(0), comment("") {}

Move::Move(int moveNumber, char player, char row, int column, std::string comment)
    : moveNumber(moveNumber), player(player), row(row), column(column), comment(comment) {}

bool Move::isValid() const {
    if (moveNumber < 1 || moveNumber > 9) return false;
    if (player != 'X' && player != 'O') return false;
    if (row != 'A' && row != 'B' && row != 'C') return false;
    if (column < 1 || column > 3) return false;
    if (!comment.empty() && comment[0] != '#') return false;
    return true;
}

std::istream& operator>>(std::istream& is, Move& move) {
    std::string line;
    std::getline(is, line);

    std::regex moveRegex(R"(^\s*(\d+)\s+([XO])\s+([ABC])(\d)(\s+#.*)?\s*$)");
    std::smatch match;

    if (std::regex_match(line, match, moveRegex)) {
        move.moveNumber = std::stoi(match[1].str());
        move.player = match[2].str()[0];
        move.row = match[3].str()[0];
        move.column = std::stoi(match[4].str());
        move.comment = match[5].str();
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.moveNumber << " " << move.player << " " << move.row << move.column;
    if (!move.comment.empty()) {
        os << " " << move.comment;
    }
    return os;
}

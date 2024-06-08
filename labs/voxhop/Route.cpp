#include "Route.h"

std::ostream& operator << (std::ostream& stream, Move move) {
  char c;

  switch(move) {
  case Move::NORTH:
    c = 'n';
    break;
  case Move::EAST:
    c = 'e';
    break;
  case Move::SOUTH:
    c = 's';
    break;
  case Move::WEST:
    c = 'w';
    break;
  case Move::UP:
    c = 'u';
    break;
  case Move::DOWN:
    c = 'd';
    break;
  default:
    c = '?';
  }

  return stream << c;
}

std::ostream& operator << (std::ostream& stream, const Route& route) {
  for(Move move: route) {
    stream << move;
  }

  return stream;
}
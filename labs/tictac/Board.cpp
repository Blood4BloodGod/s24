#include "Board.h"
#include <iostream>

Board::Board() : board(3, std::vector<char>(3, ' ')), moveCount(0) {}

bool Board::applyMove(const Move& move) {
    int row = move.row - 'A';
    int col = move.column - 1;

    if (board[row][col] != ' ') return false;

    board[row][col] = move.player;
    moveCount++;
    return true;
}

std::string Board::evaluate() const {
    if (isWin('X')) return "Game over: X wins.";
    if (isWin('O')) return "Game over: O wins.";
    if (isFull()) return "Game over: Draw.";
    return "Game in progress.";
}

bool Board::isWin(char player) const {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool Board::isFull() const {
    return moveCount == 9;
}

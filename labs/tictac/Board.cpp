#include "Board.h"
#include <iostream>

Board::Board() : grid(3, std::vector<char>(3, ' ')), isValid(true), moveCount(0), lastPlayer(' ') {}

bool Board::addMove(const Move& move) {
    int row = move.position[0] - 'A';
    int col = move.position[1] - '1';

    if (grid[row][col] != ' ') return false;

    grid[row][col] = move.player;
    moveCount++;
    lastPlayer = move.player;
    return true;
}

std::string Board::checkGameState() const {
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0] == 'X' ? "Game over: X wins." : "Game over: O wins.";
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return grid[0][i] == 'X' ? "Game over: X wins." : "Game over: O wins.";
    }
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return grid[0][0] == 'X' ? "Game over: X wins." : "Game over: O wins.";
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return grid[0][2] == 'X' ? "Game over: X wins." : "Game over: O wins.";

    bool draw = true;
    for (const auto& row : grid)
        for (char cell : row)
            if (cell == ' ')
                draw = false;

    if (draw) return "Game over: Draw.";

    if (moveCount == 0) {
        return "Game in progress: New game.";
    }

    if (lastPlayer == 'X') {
        return "Game in progress: O's turn.";
    } else {
        return "Game in progress: X's turn.";
    }
}

void Board::printBoard() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << (cell == ' ' ? '.' : cell) << ' ';
        }
        std::cout << '\n';
    }
}

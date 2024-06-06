#include "Board.h"
#include <iostream>

Board::Board() : grid(3, std::vector<char>(3, ' ')), isValid(true) {}

bool Board::addMove(const Move& move) {
    // Convert position to grid coordinates
    int row = move.position[0] - 'A';
    int col = move.position[1] - '1';

    // Check if position is already occupied or out of bounds
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ') {
        isValid = false;
        return false;
    }

    grid[row][col] = move.player;
    return true;
}

std::string Board::checkGameState() const {
    // Check rows, columns, and diagonals for a winner
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

    // Check for draw or ongoing game
    for (const auto& row : grid)
        for (char cell : row)
            if (cell == ' ')
                return "Game ongoing.";

    return "Game over: Draw.";
}

void Board::printBoard() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << (cell == ' ' ? '.' : cell) << ' ';
        }
        std::cout << '\n';
    }
}

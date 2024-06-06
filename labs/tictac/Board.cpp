#include "Board.h"
#include <iostream>
#include <unordered_set>

Board::Board() : grid(3, std::vector<char>(3, ' ')), isValid(true), moveCount(0), lastPlayer('O') {}

bool Board::addMove(const Move& move) {
    // Convert position to grid coordinates
    int row = move.position[0] - 'A';
    int col = move.position[1] - '1';

    // Check if position is already occupied or out of bounds
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ' || !isValid) {
        isValid = false;
        return false;
    }

    // Ensure players alternate correctly
    if ((move.player == 'X' && lastPlayer == 'X') || (move.player == 'O' && lastPlayer == 'O')) {
        isValid = false;
        return false;
    }

    // Ensure move numbers are in sequence and start from 1
    if (move.moveNumber != moveCount + 1) {
        isValid = false;
        return false;
    }

    grid[row][col] = move.player;
    lastPlayer = move.player;
    moveCount++;

    // Check if the game is over after this move
    std::string gameState = checkGameState();
    if (gameState.find("Game over:") != std::string::npos) {
        isValid = false;
    }

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

    // Check if the game is a draw
    bool draw = true;
    for (const auto& row : grid)
        for (char cell : row)
            if (cell == ' ')
                draw = false;

    if (draw) return "Game over: Draw.";

    // Check if no moves have been made
    if (moveCount == 0) {
        return "Game in progress: New game.";
    }

    // Check whose turn it is
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

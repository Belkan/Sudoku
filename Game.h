#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H
#include "MainAux.h"

enum status {Success, Fixed, Invalid, GameOver};

enum status set (int board[9][9], int row, int col, int value);

void hint (int board[9][9], int row, int col);

void validate (int board[9][9]);

void restart (int board[9][9]);

bool isLegalMove(int board[9][9], int row, int col, int value);

void set_in_board(int board[9][9], int row, int col, int value);

#endif

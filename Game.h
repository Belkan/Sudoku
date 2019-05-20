#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H
#include "MainAux.h"

enum status {Success, Fixed, Invalid, GameOver};

enum status set (GameState *gameState, int row, int col, int value);

void hint (GameState *gameState, int row, int col);

void validate (GameState *gameState);

void restart (GameState *gameState);

bool isLegalMove(GameState *gameState, int row, int col, int value);

#endif

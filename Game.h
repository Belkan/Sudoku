#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include "MainAux.h"

typedef enum set_status {
    SUCCESS,
    CELL_FIXED,
    ILLEGAL_MOVE,
    GAME_OVER
} SET_STATUS;

SET_STATUS set(GameState *gameState, int row, int col, int value);

void hint(GameState *gameState, int row, int col);

void validate(GameState *gameState);

void restart(GameState *gameState);

/* checks if this set is a legal set (assuming input is valid) */
bool isLegalMove(GameState *gameState, int row, int col, int value);

/* check if the board is full */
bool fullBoard(GameState *gameState);


#endif

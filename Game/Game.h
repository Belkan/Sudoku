#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H
#define BLOCK 3

#include "../MainAux/MainAux.h"
#include <string.h>

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

/* generate random solved board with H filled cells */
bool generateRandBoard(GameState *gameState, int row, int col);

/* checks if placement is legal */
bool safeMove(GameState *gameState, int row, int col, int val, char tpye);

/* Util subfunctions used for safeMove */
bool safeMoveRow(GameState *gameState, int row, int val, char type);
bool safeMoveCol(GameState *gameState, int col, int val, char type);
bool safeMoveBlock(GameState *gameState, int block, int val, char type);
int findBlock(int row, int col);

/* return number of empty cells in board */
int countBlanks(GameState *gameState, char type);

#endif

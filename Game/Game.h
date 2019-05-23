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

typedef enum board_type {
    BOARD,
    SOLUTION
} BOARD_TYPE;

SET_STATUS set(GameState *gameState, int row, int col, int value);

void hint(GameState *gameState, int row, int col);

void validate(GameState *gameState);

void restart(GameState *gameState);

/* checks if this set is a legal set (assuming input is valid) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value);

/* check if the board is full */
bool isUserBoardFull(GameState *gameState);

/* generate random solved board with H filled cells */
bool generateRandBoard(GameState *gameState, int row, int col);

/* checks if placement is legal */
bool safeMove(GameState *gameState, int row, int col, int val, BOARD_TYPE type);

/* Util subfunctions used for safeMove */
bool safeMoveRow(int** board, int row, int val, int size);
bool safeMoveCol(int** board, int col, int val, int size);
bool safeMoveBlock(int** board, int block, int val);
int findBlock(int row, int col);

/* return number of empty cells in board */
int countBlanks(GameState *gameState,  BOARD_TYPE type);

#endif

#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H
#define BLOCK 3

#include "MainAux.h"
#include <string.h>
#include <stdlib.h>



SET_STATUS set(GameState *gameState, int row, int col, int value);

void hint(GameState *gameState, int row, int col);

bool validate(GameState *gameState);

/* checks if this set is a legal set (assuming input is valid) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value);

/* check if the board is full */
bool isUserBoardFull(GameState *gameState);

/* checks if placement is legal */
bool safeMove(int **board, int row, int col, int val, int size);

/* Util subfunctions used for safeMove */
bool safeMoveRow(int** board, int row, int val, int size);
bool safeMoveCol(int** board, int col, int val, int size);
bool safeMoveBlock(int** board, int block, int val, int size);
int findBlock(int row, int col);

void setFixedCellsRand(GameState *gameState, int fixed);
void copyFromBoardToBoard(int** board1, int** board2, int size);

/* return number of empty cells in board */
int countBlanks(GameState *gameState,  BOARD_TYPE type);

void setHandler (SET_STATUS status, GameState *gameState);


#endif

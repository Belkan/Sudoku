/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H
#include <stdbool.h>

#include "Game.h"


/* Generates pseudorandom number in given range */
int getRandom(int upper, int lower);

/* Fixes alignment of matrices */
int transform(int val);

/* Util function to free resources allocated for a matrix */
void destroyMatrix(int** matrix, int size);

/* Prints the current board */
void printBoard(GameState *gameState, BOARD_TYPE type);

/* Scans number of fixed cells from the user */
int getNumberOfFixedCells();

/* Start the game. This is the sole function that should be called from main. */
void START_GAME(int n, int m, GAME_STATUS gameStatus);

/* Aux function to convert size_t to int */
int size_t2int(size_t val);
#endif

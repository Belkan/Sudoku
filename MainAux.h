
#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H

#include <stdbool.h>
#include "Game.h"

/* This module provides auxiliary methods for main.c */

/* Generates pseudorandom number in given range */
int getRandom(int lower, int upper);

/* Util function to free resources allocated for a matrix */
void destroyMatrix(int** matrix, int size);

/* Prints the current board */
void printBoard(GameState *gameState);

/* Start the game. This is the sole function that should be called from main. */
void START_GAME();

/* Aux function to convert size_t to int */
int size_t2int(size_t val);


#endif

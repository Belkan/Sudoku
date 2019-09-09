/* TODO move all utility functions used across several modules to here, for example: getNextRow() */

#ifndef SUDOKU_GENERALUTILS_H
#define SUDOKU_GENERALUTILS_H

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "Game.h"

/* Check if cell is in range for size of board. */
bool cellInRange(int cell, int size);

/* Utility function to extract integer value from string, similar to Java.  */
int nextInt(int startIdx, char *string);

#endif

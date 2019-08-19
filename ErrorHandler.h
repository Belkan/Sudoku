
#ifndef SUDOKU_ERRORHANDLER_H
#define SUDOKU_ERRORHANDLER_H
#include <stdio.h>

/* Below are errors regarding loading a board from a text file */
extern void throw_rowSizeNotFoundError();
extern void throw_colSizeNotFoundError();
extern void throw_loadedInWrongModeError();
extern void throw_loadPathError();

#endif

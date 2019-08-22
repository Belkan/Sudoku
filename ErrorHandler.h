
#ifndef SUDOKU_ERRORHANDLER_H
#define SUDOKU_ERRORHANDLER_H
#include <stdio.h>

/* Below are errors regarding loading a board from a text file */
extern void throw_rowSizeNotFoundError();
extern void throw_colSizeNotFoundError();
extern void throw_loadedInWrongModeError();
extern void throw_loadPathError();

/* Below are errors regarding the command that was given as input */
extern void throw_illegalCommandNameError();
extern void throw_illegalParameterRangeError();
extern void throw_illegalParameterValueError();
extern void throw_tooManyParamatersError();
extern void throw_tooFewParamatersError();
extern void throw_illegalCommandForCurrentMode();

#endif

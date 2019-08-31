#ifndef SUDOKU_ERRORHANDLER_H
#define SUDOKU_ERRORHANDLER_H

#include <stdio.h>

/* Below are errors regarding loading a board from a text file */
void throw_rowSizeNotFoundError();

void throw_colSizeNotFoundError();

void throw_loadedInWrongModeError();

void throw_loadPathError();

/* Below are errors regarding the command that was given as input */
void throw_illegalCommandNameError();

void throw_illegalParameterRangeError();

void throw_illegalParameterValueError();

void throw_tooManyParametersError();

void throw_tooFewParametersError();

void throw_illegalCommandForCurrentMode();

void throw_illegalCommandForCurrentMode();

void throw_unknownCommand();

void throw_nothingToUndo();

void throw_nothingToRedo();


#endif

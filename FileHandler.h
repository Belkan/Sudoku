#include <limits.h> /* PATH_MAX comes from here */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include "Game.h"
#include "MainAux.h"
#include "ErrorHandler.h"
#include "Parser.h"
#include "Solver.h"


#ifndef SUDOKU_FILEHANDLER_H
#define SUDOKU_FILEHANDLER_H

/* TODO test this function! */
/* Function to save a board to a file at a given path. Paths can be relative or absolute. */
void saveToFile (char *filePath, GameState *gameState);

/* TODO test this function! */
/* Function to load a board from a given path */
GameState *loadFromFile (char *filePath);

/* Utility function for loader: finds next position in line to read cell from. */
int getNextIdx(char *currLine, int currIdx);

/* Function to load an empty default board */
GameState *loadEmptyBoard ();

/* TODO write this function! */
/* Check if given path is valid for saving a file. */
bool validSavePath (char *filePath);

/* TODO test this function! */
/* Check if given path is valid for loading a file. */
bool validLoadPath (char *filePath);

#endif

#include <limits.h> /* PATH_MAX comes from here */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include "Game.h"
#include "Solver.h"
#include "MainAux.h"
#include "GeneralUtils.h"
#define MAX 1024

#ifndef SUDOKU_FILEHANDLER_H
#define SUDOKU_FILEHANDLER_H

/* Function to save a board to a file at a given path. Paths can be relative or absolute. */
void saveToFile (char *filePath, GameState *gameState);

/* Function to load a board from a given path */
GameState *loadFromFile (char *filePath);

/* Utility function for loader: finds next position in line to read cell from. */
int getNextIdx(char *currLine, int currIdx);

/* Utility function for loader: upon finding a number, returns the index where it ends. */
int getNumberEndPos(char *currLine, int start);

/* Function to load an empty default board */
GameState *loadEmptyBoard ();

/* Check if given path is valid for loading a file. */
bool validLoadPath (char *filePath);

/* Checks if given game state can be saved.*/
bool validSaveFile (char *filePath);

/* Check if loaded file has correct format. */
bool validFileFormat (char *filePath);


#endif

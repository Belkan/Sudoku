#include <limits.h> /* PATH_MAX comes from here */
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

#ifndef SUDOKU_FILEHANDLER_H
#define SUDOKU_FILEHANDLER_H

/* Enum to help us differentiate between relative path case and absolute path case. */
typedef enum file_path_type {
    RELATIVE,
    ABSOLUTE
} FILE_PATH_TYPE;

/* TODO write this function! */
/* Function to save a board to a file at a given path. Paths can be relative or absolute. */
void saveToFile (FILE_PATH_TYPE pathType, char *filePath, GameState *gameState, GAME_STATUS gameStatus);

/* TODO write this function! */
/* Function to load a board from a given path */
void loadFromFile (FILE_PATH_TYPE pathType, char *filePath, GameState *gameState, GAME_STATUS gameStatus);

/* TODO write this function! */
/* Construct the full path from the given relative path. */
const char * getFullPath (char *relativePath);

/* TODO write this function! */
/* Check if given path is valid for saving a file. */
bool validSavePath (char *filePath);

/* TODO write this function! */
/* Check if given path is valid for loading a file. */
bool validLoadPath (char *filePath);

/* Utility function to get realpath, from C documentation. */
char *realpath(const char *restrict_file_name, char *restrict_resolved_name);

#endif

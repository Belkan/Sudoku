#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>
#include "Game.h"
#include "FileHandler.h"
#include "ErrorHandler.h"
#include "HistoryHandler.h"
#define MAX 1024

/* Enum for the return mode of the user's request */
typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESET,
    EXIT,
    INVALID,
    GAME_OVER_STATE,
    SOLVE,
    EDIT,
    MARK_ERRORS,
    PRINT_BOARD,
    GUESS,
    GENERATE,
    UNDO,
    REDO,
    SAVE,
    GUESS_HINT,
    NUM_SOLUTIONS,
    AUTOFILL
} USER_CHOICE;

/* TODO where is this used? Gave this prefix of EXEC_ to avoid conflicts in names */
typedef enum execute_status {
    EXEC_SUCCESS_CHANGED,
    EXEC_SUCCESS_UNCHANGED,
    EXEC_CELL_FIXED,
    EXEC_SOLUTION_INCORRECT,
    EXEC_GAME_OVER_STATUS
} EXECUTE_STATUS;

/* Checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice);

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input);


#endif


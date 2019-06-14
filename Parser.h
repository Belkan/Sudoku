#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>
#include "Game.h"
#define MAX 1024

/* Enum for the return status of the user's request */
typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESTART,
    EXIT,
    INVALID,
    GAME_OVER_STATE
} USER_CHOICE;

/* Checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice);

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input, bool GameOver);


#endif


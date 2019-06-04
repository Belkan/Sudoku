#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>
#include "Game.h"
#define MAX 1024


typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESTART,
    EXIT,
    INVALID,
    GAME_OVER_STATE
} USER_CHOICE;

/* scan input from user */
USER_CHOICE parseCommand(GameState *gameState, char *input, bool GameOver);

/* check if user input in legal format */
bool matchesFormat(char* str, USER_CHOICE choice);

#endif


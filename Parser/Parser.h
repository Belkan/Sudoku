#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>
#include "../Game/Game.h"
#define MAX 1024


typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESTART,
    EXIT,
    INVALID
} USER_CHOICE;

/* scan input from user */
USER_CHOICE parseCommand(GameState *gameState, char *input);

/* check if user input in legal format */
bool matchesFormat(char* str, USER_CHOICE choice);

#endif


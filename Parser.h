#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>

typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESTART,
    EXIT
} USER_CHOICE;

/* scan input from user */
void userTurn();

/* check if user input in legal format */
bool matchesFormat(char* str, USER_CHOICE choice);

/* interpret user input */
void interpretUser(char* input);

#endif //SUDOKU_PARSER_H

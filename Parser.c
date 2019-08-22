#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"

/* Checks if user input matches given regular expressions */
bool matchesFormat(char *str, USER_CHOICE choice) {

    switch (choice) {
        case SET:
            if (strcmp(str, "set") == 0) {
                return true;
            }
            return false;
        case HINT:
            if (strcmp(str, "hint") == 0) {
                return true;
            }
            return false;
        case VALIDATE:
            if (strcmp(str, "validate") == 0) {
                return true;
            }
            return false;
        case RESTART:
            if (strcmp(str, "restart") == 0) {
                return true;
            }
            return false;
        case EXIT:
            if (strcmp(str, "exit") == 0) {
                return true;
            }
            return false;
        case EDIT:
            if(strcmp(str, "edit") == 0) {
                return true;
            }
            return false;
        case PRINT_BOARD:
            if(strcmp(str, "print_board") == 0) {
                return true;
            }
            return false;
        default:
            return false;
    }
}

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input, bool GameOver) {
    int k = 0;
    SET_STATUS set_status;
    char *str[MAX];
    char *endPtr;
    char *token = strtok(input, " \t\r\n");

    /* Reset contents of array */
    str[1] = NULL;

    while (token != 0){
        str[k++] = token;
        token = strtok(0, " \t\r\n");
    }

    if (matchesFormat(str[0], SET) && k > 3 && isdigit(*str[1]) && isdigit(*str[2]) && isdigit(*str[3]) && !GameOver) {
        set_status = set(gameState,
                          strtol(str[2], &endPtr, 10) - 1,
                          strtol(str[1], &endPtr, 10) - 1,
                          strtol(str[3], &endPtr, 10));
        setHandler(set_status, gameState);
        if (set_status == GAME_OVER){
            return GAME_OVER_STATE;
        }
        return SET;
    }
    if (matchesFormat(str[0], HINT) && k > 2 && isdigit(*str[1]) && isdigit(*str[2]) && !GameOver) {
        hint(gameState,
             strtol(str[2], &endPtr, 10) - 1,
             strtol(str[1], &endPtr, 10) - 1);
        return HINT;
    }
    if (matchesFormat(str[0], VALIDATE) && !GameOver) {
        validate(gameState);
        return VALIDATE;
    }
    if (matchesFormat(str[0], EXIT)) {
        printf("Exiting...\n");
        return EXIT;
    }
    if (matchesFormat(str[0], PRINT_BOARD)) {
        printBoard(gameState, BOARD);
        return PRINT_BOARD;
    }
    if (matchesFormat(str[0], RESTART)) {
        return RESTART;
    }
    if (matchesFormat(str[0], EDIT)) {
        if (str[1]) {
            loadFromFile(str[1], gameState);
        }
        else {
            loadEmptyBoard(gameState);
        }
        return EDIT;
    }
    return INVALID;
}


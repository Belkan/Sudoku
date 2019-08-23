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
        case RESET:
            if (strcmp(str, "reset") == 0) {
                return true;
            }
            return false;
        case EXIT:
            if (strcmp(str, "exit") == 0) {
                return true;
            }
            return false;
        case EDIT:
            if (strcmp(str, "edit") == 0) {
                return true;
            }
            return false;
        case PRINT_BOARD:
            if (strcmp(str, "print_board") == 0) {
                return true;
            }
            return false;
        default:
            return false;
    }
}

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input) {
    int k = 0, i = 0;
    char *str[MAX];
    char *endPtr;
    char *token = strtok(input, " \t\r\n");

    /* Reset contents of array */
    str[1] = NULL;

    while (token != 0) {
        str[k++] = token;
        token = strtok(0, " \t\r\n");
    }

    if (matchesFormat(str[0], SET)) {
        if (getStatus(gameState) == INITMODE) {
            throw_illegalCommandForCurrentMode();
            printf("------------------------\nDETAILS: <SET X Y Z> may only be used in EDIT or SOLVE modes.\n");
            return INVALID;
        }
        if (k > 4) {
            throw_tooManyParamatersError();
            return INVALID;
        }
        if (k < 4) {
            throw_tooFewParamatersError();
            return INVALID;
        }
        for (i = 1; i <= 3; i++) {
            if (!isdigit(*str[i])) {
                throw_illegalParameterValueError();
                printf("Parameter number %d is not a digit.\n------------------------\n", i);
                printf("DETAILS:\n<SET X Y Z> - sets cell <X,Y> to value Z.\nX,Y,Z must be non-negative integers.\n");
                return INVALID;
            }
            if (*str[i] < 0 || *str[i] > getSize(gameState)) {
                throw_illegalParameterRangeError();
                printf("Parameter number %d is not in the correct range.\n------------------------\n", i);
                printf("DETAILS:\n<SET X Y Z> - sets cell <X,Y> to value Z.\nX,Y,Z must be within the board's range!\n");
                return INVALID;
            }
        }
        return SET;
    }

    if (matchesFormat(str[0], HINT) && k == 3 && isdigit(*str[1]) && isdigit(*str[2])) {
        hint(gameState,
             strtol(str[2],
                    &endPtr, 10) - 1,
             strtol(str[1],
                    &endPtr, 10) - 1);
        return
                HINT;
    }
    if (
            matchesFormat(str[0], VALIDATE
            )) {
        validate(gameState);
        return
                VALIDATE;
    }
    if (
            matchesFormat(str[0], EXIT
            )) {
        printf("Exiting...\n");
        return
                EXIT;
    }
    if (
            matchesFormat(str[0], PRINT_BOARD
            )) {
        printBoard(gameState, BOARD
        );
        return
                PRINT_BOARD;
    }
    if (
            matchesFormat(str[0], RESET
            )) {
        return
                RESET;
    }
    if (
            matchesFormat(str[0], EDIT
            )) {
        if (str[1]) {
            loadFromFile(str[1]);
        } else {
            loadEmptyBoard(gameState);
        }
        return
                EDIT;
    }
    return
            INVALID;
}

GameState *executeCommand(GameState *gameState, USER_CHOICE commandType, char **input) {
    switch (commandType) {
        char *endPtr;
        SET_STATUS status;
        case (EDIT):
            if (!validLoadPath(input[1])) {
                throw_loadPathError();
                return gameState;
            }

        case (SET):
            status = set(gameState,
                         strtol(input[2], &endPtr, 10) - 1,
                         strtol(input[1], &endPtr, 10) - 1,
                         strtol(input[3], &endPtr, 10));
            setHandler(status, gameState);
            break;

        default:
            break;
    }
}

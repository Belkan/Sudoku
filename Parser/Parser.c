#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"
#include "../Game/Game.h"

/* checks if user input matches given regular expressions */
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
        default:
            return false;
    }
} /* EOF */

/* scan user input and return it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input) {
    int k = 0;
    SET_STATUS set_status;
    char *str[MAX];
    char *endPtr;
    char *token = strtok(input, " ");

    while (token != 0) {
        str[k] = token;
        token = strtok(0, " ");
        k++;
    }

    if (matchesFormat(str[0], SET) && isdigit(*str[1]) && isdigit(*str[2]) && isdigit(*str[3])) {
        set_status = set(gameState,
                          strtol(str[2], &endPtr, 10) - 1,
                          strtol(str[1], &endPtr, 10) - 1,
                          strtol(str[3], &endPtr, 10));
        setHandler(set_status, gameState);
        return SET;
    }
    if (matchesFormat(str[0], HINT) && isdigit(*str[1]) && isdigit(*str[2])) {
        hint(gameState,
             strtol(str[2], &endPtr, 10) - 1,
             strtol(str[1], &endPtr, 10) - 1);
        return HINT;
    }
    if (matchesFormat(str[0], VALIDATE)) {
        validate(gameState);
        return VALIDATE;
    }
    if (matchesFormat(str[0], EXIT)) {
        printf("Exiting...\n");
        return EXIT;
    }
    if (matchesFormat(str[0], RESTART)) {
        return RESTART;
    }
    return INVALID;


} /* EOF */


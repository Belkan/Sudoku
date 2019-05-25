#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"
#include "../Game/Game.h"
#define MAX 1024

/* checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice) {

    switch (choice) {
        case SET:
            if(str[0] == 's' && str[1] == 'e' && str[2] == 't' &&
                isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5])) {
                return true;
            }
        case HINT:
            if(str[0] == 'h' && str[1] == 'i' && str[2] == 'n' && str[3] == 't' &&
               isdigit(str[4]) && isdigit(str[5])) {
                return true;
            }
        case VALIDATE:
            if (strcmp(str, "validate") == 0) {
                return true;
            }
        case RESTART:
            if(strcmp(str, "restart") == 0) {
                return true;
            }
        case EXIT:
            if(strcmp(str, "exit") == 0) {
                return true;
            }
        default:
            return false;
    }
} /* EOF */

/* scan user input and return it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input) {
    int k = 0;
    char* str[MAX];
    char* token = strtok(input, " ");

    while (token != 0) {
        str[k] = token;
        token = strtok(0, " ");
    }

    if (matchesFormat(str[0], SET)) {
        setHandler(set(gameState, str[1][0], str[2][0], str[3][0]),gameState);
        return SET;
    }
    if (matchesFormat(str[0], HINT)) {
        hint(gameState, str[1][0], str[1][0]);
        return HINT;
    }
    if (matchesFormat(str[0], VALIDATE)) {
        validate(gameState);
        return VALIDATE;
    }
    if (matchesFormat(str[0], EXIT)) {
        printf("Exiting…\n");
        return EXIT;
    }
    if (matchesFormat(str[0], RESTART)) {
        return RESTART;
    }


} /* EOF */


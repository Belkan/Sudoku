#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"
#include "../Game/Game.h"
#define MAX 1024

/* checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice) {
    bool format = false;

    switch (choice) {
        case SET:
            if(str[0] == 's' && str[1] == 'e' && str[2] == 't' &&
                isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5])) {
                format = true;
                break;
            }
        case HINT:
            if(str[0] == 'h' && str[1] == 'i' && str[2] == 'n' && str[3] == 't' &&
               isdigit(str[4]) && isdigit(str[5])) {
                format = true;
                break;
            }
        case VALIDATE:
            if (strcmp(str, "validate") == 0) {
                format = true;
                break;
            }
        case RESTART:
            if(strcmp(str, "restart") == 0) {
                format = true;
                break;
            }
        case EXIT:
            if(strcmp(str, "exit") == 0) {
                format = true;
                break;
            }
    }
    return format;
} /* EOF */

/* scan user input and return it as String format */
void parseCommand(GameState *gameState, char* input) {
    bool match = false;
    int i, k;
    char clone[MAX];

    k = 0;
    /* clone input string into string without whitespaces to check formatting */
    for (i = 0; i < strlen(input) - 1; i++) {
        if (input[i] != ' ') {
            clone[k] = input[i];
            k++;
        }
    }
    /* line of blanks edge case, do nothing */
    if(strlen(clone) == 0) {
        return;
    }
    if (matchesFormat(clone, SET)) {
        match = true;
        set(gameState, clone[3], clone[4], clone[5]);
    }
    if (matchesFormat(clone, HINT)) {
        match = true;
        hint(gameState, clone[4], clone[5]);
    }
    if (matchesFormat(clone, VALIDATE)) {
        match = true;
        validate(gameState);
    }
    if (matchesFormat(clone, EXIT)) {
        printf("Exiting…\n");
        exit(EXIT_SUCCESS);
    }
    if (matchesFormat(clone, RESTART)) {
        match = true;
        restart(gameState);
    }
    if (!match) {
        printf("Error: invalid command\n");
    }
} /* EOF */
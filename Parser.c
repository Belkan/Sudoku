#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include <string.h>
#include <ctype.h>
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
void userTurn() {
    bool match = false;
    int i, k;
    char input[MAX], clone[MAX];

    while (strcmp(fgets(input, MAX, stdin), "")) { /* loop while input line not empty */
        k = 0;
        /* clone input string into string without whitespaces to check formatting */
        for (i = 0; i < strlen(input) - 1; i++) {
            if (input[i] != ' ') {
                printf("char i is : %c\n", input[i]);
                clone[k] = input[i];
                k++;
            }
        }

        if (matchesFormat(clone, SET)) {
            match = true;
            /* TODO set matrix[i][j] to input */
        }
        if (matchesFormat(clone, HINT)) {
            match = true;
            /* TODO give hint to user */
        }
        if (matchesFormat(clone, VALIDATE)) {
            match = true;
            /* TODO validate board is solvable */
        }
        if (matchesFormat(clone, EXIT)) {
            match = true;
            /* TODO exit program */
        }
        if (matchesFormat(clone, RESTART)) {
            match = true;
            /* TODO restart the game */
        }
        if (!match) {
            printf("Error: invalid command\\n");
        }
    }

} /* EOF */
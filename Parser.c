#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include <string.h>
#define MAX 1024

/* checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice) {
    /* TODO check formatting of user input */
    return true;
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
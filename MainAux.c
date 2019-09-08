
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MainAux.h"
#include "Parser.h"

/* Generates pseudorandom number in given range */
int getRandom(int lower, int upper) {
    int res;
    if (lower == upper) {
        return lower;
    }
    /* randomize result */
    res = (rand() % (upper - lower + 1)) + lower;
    return res;
}

/* Util function to free resources allocated for a matrix */
void destroyMatrix(int **matrix, int size) {
    int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/* Prints the current board */
void printBoard(GameState *gameState) {
    int row;
    int col;
    int counter;
    int value;
    int size = getSize(gameState);
    int rowsInBlock = getRowsInBlock(gameState);
    int colsInBlock = getColsInBlock(gameState);

    for (row = 0; row < size; row++) {
        if (row % rowsInBlock == 0) {
            for (counter = 0; counter < (2 * (rowsInBlock) + 1 + size * 4); counter++) {
                printf("-");
            }
            printf("\n");
        }
        for (col = 0; col < size; col++) {
            if (col % colsInBlock == 0) {
                printf("| ");
            }
            value = getCellValue(row, col, gameState);
            if (value == 0) {
                printf("    ");
            } else {
                if (value < 10) {
                    printf(" ");
                }
                printf("%d", value);
                if (isFixed(row, col, gameState) && getGameMode(gameState) == SOLVEMODE) {
                    printf(". ");
                } else if ((getMarkErrors(gameState) || getGameMode(gameState) == EDITMODE) &&
                           !isUserLegalMove(gameState, row, col, value)) {
                    printf("* ");
                } else {
                    printf("  ");
                }
            }
        }
        printf("|\n");
    }
    for (counter = 0; counter < (2 * (rowsInBlock) + 1 + size * 4); counter++) {
        printf("-");
    }
    printf("\n");
}


/* convert size_t to int */
int size_t2int(size_t val) {
    return (val <= INT_MAX) ? (int) ((ssize_t) val) : -1;
}

/* TODO make START_GAME generic for different statuses, edit/init/solve */
/* Start the game. This is the sole function that should be called from main. */
void START_GAME() {
    /*Initialize*/
    char input[MAX];
    char *parsedInput;
    USER_CHOICE command;
    HistoryState **pHistoryState = malloc(sizeof(HistoryState *));
    GameState **pGameState = malloc(sizeof(GameState *));
    int i = 0;

    /* Empty gamestate in initmode, represents the beginning of the game */
    *pGameState = createGameState(1, 1);
    *pHistoryState = createHistoryState();

    printf("-----------TAUDOKU-----------\n");
    printf("Enter a command of your choice:\n");

/* Start game. Each loop is a line fed by the user. */
    while (fgets(input, MAX, stdin)) {
        i = 0;
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n') {
            if (input[i] == '\n') {
                break;
            }
            i++;
        }
        if (input[i] == '\n') {
            continue;
        }
        parsedInput = strtok(input, "\n");
        command = parseCommand(pGameState, parsedInput);

        executeCommand(pGameState, pHistoryState, command, input);

        checkFullBoard(*pGameState);
    }
}


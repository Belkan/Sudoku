#include "MainAux.h"
#include "Solver.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
void printBoard(GameState *gameState, BOARD_TYPE type) {
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
            value = getCellValue(row, col, gameState, type);
            if (value == 0) {
                printf("    ");
            } else {
                if (value < 10) {
                    printf(" ");
                }
                if (isFixed(row, col, gameState)) {
                    printf(".");
                } else {
                    printf(" ");
                }
                printf("%d ", value);
            }
        }
        printf("|\n");
    }
    for (counter = 0; counter < (2 * (rowsInBlock) + 1 + size * 4); counter++) {
        printf("-");
    }
    printf("\n");
}

/* Scans number of fixed cells from the user */
int getNumberOfFixedCells() {
    int fixed;
    char input[MAX];
    char *endPtr;
    int i = 0;

    printf("Please enter the number of cells to fill [0-80]:\n");

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
        fixed = strtol(input, &endPtr, 10);
        if (fixed < 0 || fixed > 80) {
            printf("Error: invalid number of cells to fill (should be between 0 and 80)\n"
                   "Please enter the number of cells to fill [0-80]:\n");
            continue;
        }
        return fixed;
    }
    return -1;
}

/* convert size_t to int */
int size_t2int(size_t val) {
    return (val <= INT_MAX) ? (int)((ssize_t)val) : -1;
}

/* TODO make START_GAME generic for different statuses, edit/init/solve */
/* Start the game. This is the sole function that should be called from main. */
void START_GAME() {
    /*Initialize*/
    char input[MAX];
    USER_CHOICE status;
    bool gameOver = false;
    int i = 0;

    /* Empty gamestate in initmode, represents the beginning of the game */
    GameState *gameState = createGameState(1,1);

    printf("-----------TAUDOKU-----------\n");
    printf("Enter a command of your choice:\n");

/* Start game */
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
        status = parseCommand(gameState, strtok(input, "\n"));
        if (status == EXIT) {
            exit(EXIT_SUCCESS);
        }
        if (status == INVALID) {
            printf("Error: invalid command\n");
        }

        if (status == GAME_OVER_STATE) {
            gameOver = true;
        }
    }
    printf("Exiting...\n");
    destroyGameState(gameState);
}


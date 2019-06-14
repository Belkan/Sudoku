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

/* Fixes alignment of matrices */
int transform(int val) {
    if (val >= 1 && val <= 4) {
        return val - 2;
    }
    if (val >= 6 && val <= 8) {
        return val - 3;
    }
    if (val >= 10 && val <= 12) {
        return val - 4;
    }
    return 0;
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
    for (row = 1; row <= 13; row++) {
        for (col = 1; col <= 13; col++) {
            if (isSeparatorRow(row)) {
                col = 1;
                row++;
                printf("----------------------------------\n");
                if (row == 14) {
                    return;
                }
                printf("| ");
            } else if (isSeparatorCol(col)) {
                if (col == 13)
                    printf("|\n"); /* we have reached end of columns, go down one line */
                else
                    printf("| ");
            } else {
                if (isFixed(transform(row),transform(col),gameState)) {
                    printf(".%d ", getCellValue(transform(row), transform(col), gameState, type));
                } else if (getCellValue(transform(row), transform(col), gameState, type) == 0) {
                    printf("   ");
                } else {
                    printf(" %d ", getCellValue(transform(row), transform(col), gameState, type));
                }
            }
        }
    }
}

/* Subfunctions for printBoard */
bool isSeparatorRow(int row) {
    if (row == 1 || row == 5 || row == 9 || row == 13) {
        return true;
    }
    return false;
}
bool isSeparatorCol(int col) {
    if (col == 1 || col == 5 || col == 9 || col == 13) {
        return true;
    }
    return false;
}


/* Scans number of fixed cells from the user */
int getNumberOfFixedCells() {
    int fixed;
    char input[MAX];
    char* endPtr;
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



/* Start the game. This is the sole function that should be called from main. */
void START_GAME() {
     /*Initialize*/
    char input[MAX];
    USER_CHOICE status;
    bool gameOver = false;
    int i = 0;

    GameState *gameState = initializeGame();

    printBoard(gameState, BOARD);

/* Start game */
    while (fgets(input, MAX, stdin)){
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
        status = parseCommand(gameState, strtok(input,"\n"), gameOver);
        if (status == EXIT) {
            exit(EXIT_SUCCESS);
        }
        if (status == INVALID) {
            printf("Error: invalid command\n");
        }
        if (status == RESTART){
            destroyGameState(gameState);
            gameState = initializeGame();
            printBoard(gameState, BOARD);
            gameOver = false;
        }
        if (status == GAME_OVER_STATE) {
            gameOver = true;
        }
    }
    printf("Exiting...\n");
    destroyGameState(gameState);
}

/* Initializes the struct for the game */
GameState* initializeGame(){
    GameState *gameState = createGameState(SIZE);
    generateRandomSolution(gameState);
    copyFromBoardToBoard(gameState, SOLUTION, gameState, BOARD);
    setFixedCellsRand(gameState, getNumberOfFixedCells());
    return gameState;
}
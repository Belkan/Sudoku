#include "MainAux.h"
#include "../Solver/Solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* generates pseudorandom number in given range */
int getRandom(int lower, int upper) {
    if (lower == upper) {
        return lower;
    }
    /* randomize result */
    int res = (rand() % (upper - lower + 1)) + lower;
    return res;
} /* EOF */

/* fixes alignment of matrices */
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
} /* EOF */


/* creates a new GameState of Sudoku with Size rows/columns*/
GameState *createGameState(int size) {
    GameState *gameState = malloc(sizeof(GameState));
    gameState->size = size;

    gameState->board = (int **) malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        gameState->board[i] = calloc(size, sizeof(int));
    }

    gameState->solution = (int **) malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        gameState->solution[i] = calloc(size, sizeof(int));
    }

    gameState->fixed = (bool **) malloc(size * sizeof(bool *));
    for (int i = 0; i < size; i++) {
        gameState->fixed[i] = (bool *) calloc(size, sizeof(bool));
    }

    return gameState;
}

/* frees all allocated memory */
void destroyGameState(GameState *gameState) {
    destroyMatrix(gameState->board, gameState->size);
    destroyMatrix(gameState->solution, gameState->size);
    destroyMatrix(gameState->fixed, gameState->size);
    free(gameState);
}

void destroyMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/* prints the current board */
/* TODO test this method */
void printBoard(GameState *gameState, BOARD_TYPE type) {
    int row;
    int col;
    int **board;
    switch (type) {
        case (BOARD):
            board = gameState->board;
            break;
        case (SOLUTION):
            board = gameState->solution;
            break;
    }
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
                if (gameState->fixed[transform(row)][transform(col)]) {
                    printf(".%d ", board[transform(row)][transform(col)]);
                } else if (board[transform(row)][transform(col)] == 0) {
                    printf("   ");
                } else {
                    printf(" %d ", board[transform(row)][transform(col)]);
                }
            }
        }
    }
} /* EOF */

/* checks if row is a separator row */
bool isSeparatorRow(int row) {
    if (row == 1 || row == 5 || row == 9 || row == 13) {
        return true;
    }
    return false;
} /* EOF */

/* checks if column is a separator columns */
bool isSeparatorCol(int col) {
    if (col == 1 || col == 5 || col == 9 || col == 13) {
        return true;
    }
    return false;
} /* EOF */


int getNumberOfFixedCells() {
    int fixed;
    printf("Please enter the number of cells to fill [0-80]:\n");
    scanf("%d", &fixed);
    return fixed;
}

void restart() {}


void START_GAME() {
    // Initialize
    GameState *gameState = createGameState(SIZE);
    generateRandomSolution(gameState);
    copyFromBoardToBoard(gameState->solution, gameState->board, gameState->size);
    setFixedCellsRand(gameState, getNumberOfFixedCells());


    destroyGameState(gameState);
}
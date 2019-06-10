#include "MainAux.h"
#include "Solver.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* generates pseudorandom number in given range */
int getRandom(int lower, int upper) {
    int res;
    if (lower == upper) {
        return lower;
    }
    /* randomize result */
    res = (rand() % (upper - lower + 1)) + lower;
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
    return 0;
}/* EOF */


/* creates a new GameState of Sudoku with Size rows/columns*/
GameState *createGameState(int size) {
    int i;
    GameState *gameState = malloc(sizeof(GameState));
    gameState->size = size;

    gameState->board = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        gameState->board[i] = calloc(size, sizeof(int));
    }

    gameState->solution = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        gameState->solution[i] = calloc(size, sizeof(int));
    }

    gameState->fixed = (bool **) malloc(size * sizeof(bool *));
    for (i = 0; i < size; i++) {
        gameState->fixed[i] = (bool *) calloc(size, sizeof(bool));
    }

    return gameState;
}

/* frees all allocated memory */
void destroyGameState(GameState *gameState) {
    destroyMatrix(gameState->board, gameState->size);
    destroyMatrix(gameState->solution, gameState->size);
    destroyMatrix((int**) gameState->fixed, gameState->size);
    free(gameState);
}

void destroyMatrix(int **matrix, int size) {
    int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/* prints the current board */
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

GameState* initializeGame(){
    GameState *gameState = createGameState(SIZE);
    generateRandomSolution(gameState);
    copyFromBoardToBoard(gameState->solution, gameState->board, gameState->size);
    setFixedCellsRand(gameState, getNumberOfFixedCells());
    return gameState;
}

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

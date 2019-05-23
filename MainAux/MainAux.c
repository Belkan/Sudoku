#include "MainAux.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* generates pseudorandom number in given range */
int getRandom(int lower, int upper)
{
    /* generate new seed */
    time_t t;
    srand((unsigned) time(&t));

    /* randomize result */
    int res = (rand() % (upper - lower + 1)) + lower;
    return res;
} /* EOF */

/* fixes alignment of matrices */
int transform(int val) {
    if (val >= 1 && val <= 4) {
        return val-2;
    }
    if (val >= 6 && val <= 8) {
        return val-3;
    }
    if (val >= 10 && val <= 12) {
        return val-4;
    }
} /* EOF */

/* check if given fixed value is in range */
bool legalFixed(int fixed) {
    if (fixed > 80 || fixed < 0) {
        return false;
    }
    return true;
} /* EOF */

/* creates a new GameState of Sudoku with Size rows/columns*/
    GameState* createGameState(int size) {
    GameState* gameState = malloc(sizeof(GameState));
    gameState->size = size;

    gameState->board =  malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++){
        gameState->board[i] =  calloc(size, sizeof(int));
    }

    gameState->solution =  malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++){
        gameState->solution[i] =  calloc(size, sizeof(int));
    }

    gameState->fixed = (bool**) malloc(size * sizeof(bool*));
    for (int i = 0; i < size; i++){
        gameState->fixed[i] = (bool*) calloc(size, sizeof(bool));
    }

    return gameState;
}

/* frees all allocated memory */
void destroyGameState(GameState* gameState){
    for (int i = 0; i < gameState->size; i++){
        free(gameState->board[i]);
        free(gameState->solution[i]);
        free(gameState->fixed[i]);
    }
    free(gameState->board);
    free(gameState->solution);
    free(gameState->fixed);
    free(gameState);
    }

/* prints the current board */
/* TODO test this method */
void printBoard(GameState *gameState) {
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
            }
            else if (isSeparatorCol(col)) {
                if (col == 13)
                    printf("|\n"); /* we have reached end of columns, go down one line */
                else
                    printf("| ");
            }
            else {
                if (isFixed(transform(row), transform(col), gameState)){
                    printf(".%d ", gameState->board[transform(row)][transform(col)]);
                }
                else {
                    printf(" %d ", gameState->board[transform(row)][transform(col)]);
                }
            }
        }
    }
} /* EOF */

/* checks if row is a separator row */
bool isSeparatorRow(int row) {
    if (row == 1 || row == 5 || row == 9 || row == 13){
        return true;
    }
    return false;
} /* EOF */

/* checks if column is a separator columns */
bool isSeparatorCol(int col) {
    if (col == 1 || col == 5 || col == 9 || col == 13){
        return true;
    }
    return false;
} /* EOF */

/* checks if cell is fixed */
bool isFixed (int row, int col, GameState *gameState){
    return gameState->fixed[row][col];
} /* EOF */

bool inBounds(int row, int col) {
    if (row < 0 || row > 8 || col < 0 || col > 8) {
        return false;
    }
    return true;
} /* EOF */
#include "MainAux.h"
#include <Stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 9

/* fixes alignment of matrices */
int transform(int row) {
    if (row >= 1 && row <= 4) {
        return row-1;
    }
    if (row >= 6 && row <= 8) {
        return row-2;
    }
    if (row >= 10 && row <= 12) {
        return row-3;
    }
} /* EOF */

/* this method initializes all matrices of game state, returns empty struct */
struct GameState initializeGame() {
    int emptyMatrix[SIZE][SIZE] = {{}};
    int *ptr = &emptyMatrix[SIZE][SIZE];
    bool emptyMatrixBool[SIZE][SIZE] = {{}};
    bool *ptrBool = &emptyMatrixBool[SIZE][SIZE];
    /* set all of the matrices of the game state to empty 9x9 square matrices */
    GameState gameState = { &ptr, &ptr, &ptrBool};
    return gameState; /* return empty game */
} /* EOF */

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
            }
            else if (isSeparatorCol(col)) {
                if (col == 13)
                    printf("|\n"); /* we have reached end of columns, go down one line */
                else
                    printf("|");
                continue;
            }
            else {
                if (isFixed(row, col, gameState)){
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
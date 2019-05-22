#include "MainAux.h"
#include <Stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// TODO: Not sure what you did here, but it fucked things up.
///* this method initializes all matrices of game state, returns empty struct */
//struct GameState initializeGame() {
//    int emptyMatrix[SIZE][SIZE] = {{}};
//    int *ptr = &emptyMatrix[SIZE][SIZE];
//    bool emptyMatrixBool[SIZE][SIZE] = {{}};
//    bool *ptrBool = &emptyMatrixBool[SIZE][SIZE];
//    /* set all of the matrices of the game state to empty 9x9 square matrices */
//    GameState gameState = { &ptr, &ptr, &ptrBool};
//    return gameState; /* return empty game */
//} /* EOF */

/// This works for now.
    GameState* initializeGame(int Size) {
    GameState* gameState = malloc(sizeof(GameState));

    gameState->board =  malloc(Size * sizeof(int*));
    for (int i = 0; i < Size; i++){
        gameState->board[i] =  calloc(Size, sizeof(int));
    }

    gameState->solution =  malloc(Size * sizeof(int*));
    for (int i = 0; i < Size; i++){
        gameState->solution[i] =  calloc(Size, sizeof(int));
    }

    gameState->fixed = (bool**) malloc(Size * sizeof(bool*));
    for (int i = 0; i < Size; i++){
        gameState->fixed[i] = (bool*) calloc(Size, sizeof(bool));
    }

    return gameState;
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
#include "MainAux.h"
#include <Stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
}

/* checks if row is a separator row */
bool isSeparatorRow(int row) {
    if (row == 1 || row == 5 || row == 9 || row == 13){
        return true;
    }
    return false;
}

/* checks if column is a separator columns */
bool isSeparatorCol(int col) {
    if (col == 1 || col == 5 || col == 9 || col == 13){
        return true;
    }
    return false;
}

/* checks if cell is fixed */
bool isFixed (int row, int col, GameState *gameState){
    return gameState->fixed[row][col];
}
#include "MainAux.h"
#include <Stdio.h>
#include <stdlib.h>
#define SEPARATOR_ROW (row == 1 || row == 5 || row == 9 || row == 13)
#define SEPARATOR_COL (col == 1 || col == 5 || col == 9 || col == 13)
#define FIXED isFixed(row, col, board))

int transformRow(int row) { /* method to fix alignment of matrices */
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


/* method used to print the current board */
int row;
int col;

/* TODO test this method */
void printBoard(int board [9][9]) {
    for (row = 1; row <= 13; row++) {
        for (col = 1; col <= 13; col++) {

            if SEPARATOR_ROW {
                col = 1;
                row++;
                printf("----------------------------------\n");
            }

            else if SEPARATOR_COL {
                if (col == 13)
                    printf("|\n"); /* we have reached end of columns, go down one line */
                else
                    printf("|");
                continue;
            }

            else {
                if (FIXED) { /* TODO make sure there is actually isFixed function */
                    printf(".%d ", board[transformRow(row)][transformRow(col)]);
                }
                else {
                    printf(" %d ", board[transformRow(row)][transformRow(col)]);
                }
            }
        }
    }
} /* EOF */
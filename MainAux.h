/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H
#include <stdbool.h>

/* prints the current board */
void printBoard(int board [9][9]);

/* initializes board */
void initializeGame(int board[9][9]);

/* checks if cell is fixed */
bool isFixed(int row, int col, int board[9][9]);

/* fixes alignment of matrices */
int transformRow(int row);

bool separator_row (int row);

bool separator_col (int row);



#endif //SUDOKU_MAINAUX_H

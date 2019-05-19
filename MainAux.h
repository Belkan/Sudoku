/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H

/* utility function to print board */
void printBoard(int board [9][9]);

/* function to initialize board */
void initializeGame(int board[9][9]);

/* function to check if cell is fixed */
int isFixed(int row, int col, int board[9][9]);

/* method to fix alignment of rows/columns when printing */
int transformRow(int row);

#endif //SUDOKU_MAINAUX_H

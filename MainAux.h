/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H

/* function to print board in correct format */
void printBoard(int board [9][9]);

/* function to initialize the board */
void initializeGame(int board[9][9]);

/* function to determine if board[x][y] is fixed */
int isFixed(int row, int col, int board[9][9]);

#endif //SUDOKU_MAINAUX_H

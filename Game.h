#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

/**/
void set (int board[9][9], int x, int y, int z);

void hint (int board[9][9], int x, int y);

void validate (int board[9][9]);

void restart (int board[9][9]);

void exit();



#endif

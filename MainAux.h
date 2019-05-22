/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H
#include <stdbool.h>
#define SIZE 9

typedef struct GameState{
    int **board;
    int **solution;
    bool **fixed;
} GameState;

/* prints the current board */
void printBoard(GameState *gameState);

/* initializes board */
GameState* initializeGame(int Size);

/* checks if cell is fixed */
bool isFixed(int row, int col, GameState *gameState);

/* fixes alignment of matrices */
int transform(int row);

bool isSeparatorRow(int row);

bool isSeparatorCol(int row);



#endif //SUDOKU_MAINAUX_H
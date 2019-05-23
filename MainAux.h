/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H
#include <stdbool.h>
#define SIZE 9

typedef struct GameState{
    int size;
    int **board;
    int **solution;
    bool **fixed;
} GameState;

/* generate random number in given range */
int getRandom(int upper, int lower);

/* prints the current board */
void printBoard(GameState *gameState);

/* destroys game board and frees allocated resources */
void destroyGameState(GameState* gameState);

/* initializes board */
GameState* createGameState(int size);

/* checks if cell is fixed */
bool isFixed(int row, int col, GameState *gameState);

/* fixes alignment of matrices */
int transform(int val);

/* check if given fixed value is in range */
bool legalFixed(int fixed);

bool isSeparatorRow(int row);

bool isSeparatorCol(int row);



#endif //SUDOKU_MAINAUX_H
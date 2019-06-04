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

typedef enum set_status {
    SUCCESS,
    CELL_FIXED,
    ILLEGAL_MOVE,
    GAME_OVER
} SET_STATUS;

typedef enum board_type {
    BOARD,
    SOLUTION
} BOARD_TYPE;

/* generate random number in given range */
int getRandom(int upper, int lower);

/* prints the current board */
void printBoard(GameState *gameState, BOARD_TYPE type);

/* destroys game board and frees allocated resources */
void destroyGameState(GameState* gameState);

void destroyMatrix(int** matrix, int size);

/* initializes board */
GameState* createGameState(int size);

/* checks if cell is fixed */

/* fixes alignment of matrices */
int transform(int val);

bool isSeparatorRow(int row);

bool isSeparatorCol(int row);

void restart();

void START_GAME();

#endif

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

/* initializes board */
GameState* createGameState(int size);

/* checks if cell is fixed */
bool isFixedCell(int row, int col, GameState *gameState);

/* fixes alignment of matrices */
int transform(int val);

/* check if given fixed value is in range */
bool legalFixed(int fixed);

bool isSeparatorRow(int row);

bool isSeparatorCol(int row);

bool inBounds(int row, int col);

void restart();

void START_GAME();

#endif //SUDOKU_MAINAUX_H
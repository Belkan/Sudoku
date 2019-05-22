/* functions to handle auxiliary methods */

#ifndef SUDOKU_MAINAUX_H
#define SUDOKU_MAINAUX_H
#include <stdbool.h>
#define SIZE 9

typedef struct GameState{
    int board[SIZE][SIZE];
    int solution[SIZE][SIZE];
    bool fixed[SIZE][SIZE];
} GameState;

/* prints the current board */
void printBoard(GameState *gameState);

/* initializes board */
struct GameState initializeGame();

/* checks if cell is fixed */
bool isFixed(int row, int col, GameState *gameState);

/* fixes alignment of matrices */
int transform(int row);

bool isSeparatorRow(int row);

bool isSeparatorCol(int row);



#endif //SUDOKU_MAINAUX_H
#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "Game.h"

typedef enum solution_type {
    DETERMINISTIC,
    RANDOM
} SOLUTION_TYPE ;

/* Checks if there is a solution to the board. Assumes solution is empty. */
bool isSolvableRecursion(GameState *gameState, int row, int col, SOLUTION_TYPE type);
/* Subfunctions for isSolvableRecursion */
int getNextRow(int size, int row, int col);
int getNextCol(int size, int col);
void swap(int *x, int *y);

/* Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.*/
bool isSolvable(GameState *gameState);

/* Generates the initial random solution. Assumes solution is empty.*/
void generateRandomSolution(GameState *gameState);



#endif


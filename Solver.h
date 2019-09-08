#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "Game.h"
#include "SolverUtils.h"

typedef enum solution_type {
    DETERMINISTIC,
    RANDOM
} SOLUTION_TYPE ;

/* TODO compare this with Ellie & Nofar */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState);

/* Checks if there is a solution to the board. Assumes solution is empty. */
bool isSolvableRecursion(GameState *gameState, int row, int col, SOLUTION_TYPE type);

/* Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.*/
bool isSolvable(GameState *gameState);

/* Generates the initial random solution. Assumes solution is empty.*/
void generateRandomSolution(GameState *gameState);

#endif


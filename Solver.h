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

/* TODO Gurobi needs to check if board is solvable */
bool isSolvable(GameState *gameState);

#endif


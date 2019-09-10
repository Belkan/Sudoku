#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "Game.h"
#include "SolverUtils.h"

typedef struct Gurobi {
    double* solution;
    int error;

} Gurobi ;

typedef enum LinearMethod {
    ILP,
    LP
} LinearMethod;

/* TODO compare this with Ellie & Nofar */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState);

Gurobi* getSolution(GameState *gameState, LinearMethod linearMethod);

/* TODO Gurobi needs to check if board is solvable */
bool isSolvable(GameState *gameState);

Gurobi* createGurobi(int size) {
    Gurobi* gurobi = malloc(sizeof(Gurobi));
    gurobi->solution = (double*) malloc(size*sizeof(double));
    return gurobi;
}

#endif


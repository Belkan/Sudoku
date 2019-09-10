#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdbool.h>
#include "Game.h"
#include "SolverUtils.h"

typedef struct SolutionContainer {
    double *solution;
    int ***variables;
    int numOfVariables;
    int error;
    bool solutionFound;

} SolutionContainer;

typedef enum LinearMethod {
    ILP,
    LP
} LinearMethod;

/* TODO compare this with Ellie & Nofar */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState);

SolutionContainer *getSolution(GameState *gameState, LinearMethod linearMethod);

/* TODO SolutionContainer needs to check if board is solvable */
bool isSolvable(GameState *gameState);

SolutionContainer *createSolutionContainer(int size);

void destroySolutionContainer(SolutionContainer* solutionContainer);

void destorySolution();

void destroyGurobi(GRBenv* env, GRBmodel* model, double* obj, char* variableTypes, int* ind, double* val);


#endif


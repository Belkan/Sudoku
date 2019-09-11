#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdbool.h>
#include "gurobi_c.h"
#include "Game.h"
#include "SolverUtils.h"

typedef struct SolutionContainer {
    double *solution;
    int ***variables;
    int numOfVariables;
    int error;
    int boardSize;
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

SolutionContainer *createSolutionContainer(int size);

void destroySolutionContainer(SolutionContainer* solutionContainer);

void destroyGurobi(GRBenv* env, GRBmodel* model, double* obj, char* variableTypes, int* ind, double* val);

int getValueFromILPSolution(SolutionContainer* solutionContainer, int row, int col) ;

int getIndexOfVariable(SolutionContainer* solutionContainer, int row, int col, int val);

void setIndexOfVariable(SolutionContainer* solutionContainer, int row, int col, int val, int idx);
#endif


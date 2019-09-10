#include <stdlib.h>
#include "Solver.h"
#include "MainAux.h"

/* TODO compare with Ellie & Nofar num of solutions on various boards to ensure correctness. */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState) {
    bool foundMove = false, reachedEnd = false;
    int row = 0, col = 0, size = getSize(gameState), solutions = 0, idx = 0, move = -1;
    struct recursion_stack *stack = createStack(gameState->size * gameState->size);

    /* Iterating until stack empties replaces recursion. */
    while (!isEmpty(stack)) {
        foundMove = false, reachedEnd = false;
        row = peekRow(stack), col = peekCol(stack);
        move = -1;

        /* Flag checks if we have reached the end of the board. */
        reachedEnd = (row == size - 1 && col == size - 1);

        /* Handle edge case: fixed cells. */
        if (isFixed(row, col, gameState)) {
            if (!reachedEnd) {
                push(stack, getNextRow(size, row, col), getNextCol(size, col));
                continue;
            } else {
                solutions++;
                pop(stack);
                continue;
            }
        }

        /* Attempt to find a legal move for current cell, starting from its current value + 1. */
        for (idx = getCellValue(row, col, gameState) + 1; idx <= size; idx++) {
            if (safeMove(row, col, idx, gameState)) {
                move = idx;
                foundMove = true;
                break;
            }
        }

        /* Case we have reached the end: attempt all possible values and increment counter. */
        if (reachedEnd) {
            for (idx = 1; idx <= size; idx++) {
                if (safeMove(row, col, idx, gameState)) {
                    solutions++;
                }
            }
            /* Backtrack to node before last node. */
            pop(stack);
            continue;
        }

            /* Case we haven't reached the end yet. */
        else {
            /* Found a move and haven't finished yet. Set cell to move found and go to next stack call by pushing. */
            if (foundMove) {
                setCellValue(row, col, move, gameState);
                push(stack, getNextRow(size, row, col), getNextCol(size, col));
                continue;
            } else {
                /* Didn't find a move and didn't finish yet. Set cell to 0 and backtrack by popping. */
                setCellValue(row, col, 0, gameState);
                pop(stack);
                continue;
            }
        }
    }
    printBoard(gameState);
    destroyStack(stack);
    return solutions;
}

SolutionContainer *getSolution(GameState *gameState, LinearMethod linearMethod) {
    GRBenv *env = NULL;
    GRBmodel *model = NULL;
    int size = getSize(gameState);
    int error = 0;
    double *sol;
    int *ind;
    double *val;
    double *obj;
    char *variableTypes;
    int optimstatus;
    double objval;
    SolutionContainer *solutionContainer = createSolutionContainer(size);
    int row, firstRow, lastRow, col, firstCol, lastCol, value, totalVariableCount, i, variablesInConstraint, block;
    int rowsInBlock = getRowsInBlock(gameState), colsInBlock = getColsInBlock(gameState);

    /* Create environment - log file is solutionContainer.log */
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {
        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
        GRBfreeenv(env);
        solutionContainer->error = error;
        return solutionContainer;
    }

    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        GRBfreeenv(env);
        solutionContainer->error = error;
        return solutionContainer;
    }
    /* Create an empty model named "sudoku" */
    error = GRBnewmodel(env, &model, "sudoku", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
        GRBfreemodel(model);
        GRBfreeenv(env);
        solutionContainer->error = error;
        return solutionContainer;
    }

    /* Add only variables that are legal for the current board state. */
    totalVariableCount = 0;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            /* Only add variables for empty cells */
            if (getCellValue(row, col, gameState) == 0) {
                for (value = 1; value <= size; value++) {
                    /* Only add variable for valid values */
                    if (isUserLegalMove(gameState, row, col, value)) {
                        solutionContainer->variables[row][col][value - 1] = totalVariableCount++;
                    }
                }
            }
        }
    }

    obj = malloc(totalVariableCount * sizeof(double));
    variableTypes = malloc(totalVariableCount * sizeof(char));

    /* Set target function and variable types per linear method */
    switch (linearMethod) {
        case (ILP):
            for (i = 0; i < totalVariableCount; i++) {
                obj[i] = 0;
                variableTypes[i] = GRB_BINARY;
            }
            break;
        case (LP) :
            for (i = 0; i < totalVariableCount; i++) {
                obj[i] = getRandom(1, 5);
                variableTypes[i] = GRB_CONTINUOUS;
            }
            break;
    }

    ind = malloc(totalVariableCount * sizeof(int));
    val = malloc(totalVariableCount * sizeof(double));

    /* Add variables to model */
    error = GRBaddvars(model, totalVariableCount, 0, NULL, NULL, NULL, obj, NULL, NULL, variableTypes, NULL);
    if (error) {
        printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    /* Change objective sense to maximization */
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    /* update the model - to integrate new variables */

    error = GRBupdatemodel(model);
    if (error) {
        printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    /* Set 1st constraint: each cell has exactly 1 value. */
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            variablesInConstraint = 0;
            for (value = 1; value <= size; value++) {
                if (solutionContainer->variables[row][col][value - 1] > -1) {
                    ind[variablesInConstraint] = solutionContainer->variables[row][col][value - 1];
                    val[variablesInConstraint] = 1;
                    variablesInConstraint++;
                }
            }
            if (variablesInConstraint == 0) {
                continue;
            }
            /* x_[row, col, 1] + ... + x_[row, col, variablesInConstraint] = 1 */
            error = GRBaddconstr(model, variablesInConstraint, ind, val, GRB_EQUAL, 1.0, "c1");
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                solutionContainer->error = error;
                destroyGurobi(env, model, obj, variableTypes, ind, val);
                return solutionContainer;
            }
        }
    }

    /* Set 2nd constraint: each row has exactly one of each value. */
    for (row = 0; row < size; row++) {
        for (value = 1; value <= size; value++) {
            variablesInConstraint = 0;
            for (col = 0; col < size; col++) {
                if (solutionContainer->variables[row][col][value - 1] > -1) {
                    ind[variablesInConstraint] = solutionContainer->variables[row][col][value - 1];
                    val[variablesInConstraint] = 1;
                    variablesInConstraint++;
                }
            }
            if (variablesInConstraint == 0) {
                continue;
            }
            error = GRBaddconstr(model, variablesInConstraint, ind, val, GRB_EQUAL, 1.0, "c2");
            if (error) {
                printf("ERROR %d 2nd GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                solutionContainer->error = error;
                destroyGurobi(env, model, obj, variableTypes, ind, val);
                return solutionContainer;
            }
        }
    }

    /* Set 3rd constraint: each col has exactly one of each value. */
    for (col = 0; col < size; col++) {
        for (value = 1; value <= size; value++) {
            variablesInConstraint = 0;
            for (row = 0; row < size; row++) {
                if (solutionContainer->variables[row][col][value - 1] > -1) {
                    ind[variablesInConstraint] = solutionContainer->variables[row][col][value - 1];
                    val[variablesInConstraint] = 1;
                    variablesInConstraint++;
                }
            }
            if (variablesInConstraint == 0) {
                continue;
            }
            error = GRBaddconstr(model, variablesInConstraint, ind, val, GRB_EQUAL, 1.0, "c3");
            if (error) {
                printf("ERROR %d 3rd GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                solutionContainer->error = error;
                destroyGurobi(env, model, obj, variableTypes, ind, val);
                return solutionContainer;
            }
        }
    }

    /* Set 4th constraint: each block has exactly one of each value. */
    for (block = 0; block < size; block++) {
        for (value = 1; value <= size; value++) {
            variablesInConstraint = 0;
            firstRow = (block / rowsInBlock) * rowsInBlock;
            lastRow = firstRow + rowsInBlock - 1;
            for (row = firstRow; row <= lastRow; row++) {
                firstCol = (block % rowsInBlock) * colsInBlock;
                lastCol = firstCol + colsInBlock - 1;
                for (col = firstCol; col <= lastCol; col++) {
                    if (solutionContainer->variables[row][col][value - 1] > -1) {
                        ind[variablesInConstraint] = solutionContainer->variables[row][col][value - 1];
                        val[variablesInConstraint] = 1;
                        variablesInConstraint++;
                    }
                }
            }
            if (variablesInConstraint == 0) {
                continue;
            }
            error = GRBaddconstr(model, variablesInConstraint, ind, val, GRB_EQUAL, 1.0, "c4");
            if (error) {
                printf("ERROR %d 4th GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                solutionContainer->error = error;
                destroyGurobi(env, model, obj, variableTypes, ind, val);
                return solutionContainer;
            }
        }
    }

    /* Optimize model - need to call this before calculation */
    error = GRBoptimize(model);
    if (error) {
        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    /* Write model to 'mip1.lp' - this is not necessary but very helpful */
    error = GRBwrite(model, "sudoku.lp");
    if (error) {
        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    /* Get solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) {
        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
        solutionContainer->error = error;
        destroyGurobi(env, model, obj, variableTypes, ind, val);
        return solutionContainer;
    }

    sol = malloc(totalVariableCount * sizeof(double));
    /* get the objective -- the optimal result of the function */
    if (optimstatus == GRB_OPTIMAL) {
        error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
        if (error) {
            printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
            solutionContainer->error = error;
            destroyGurobi(env, model, obj, variableTypes, ind, val);
            return solutionContainer;
        }

        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, totalVariableCount, sol);
        if (error) {
            printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
            solutionContainer->error = error;
            destroyGurobi(env, model, obj, variableTypes, ind, val);
            return solutionContainer;
        }
    }
    /* print results */
    printf("\nOptimization complete\n");
    solutionContainer->solution = sol;

    /* solution found */
    if (optimstatus == GRB_OPTIMAL) {
        solutionContainer->solutionFound = true;
        printf("Optimal\n");
    }
        /* no solution found */
    else if (optimstatus == GRB_INF_OR_UNBD) {
        solutionContainer->solutionFound = false;
        printf("Not found\n");
    }
        /* error or calculation stopped */
    else {
        printf("Optimization was stopped early\n");
    }
    destroyGurobi(env, model, obj, variableTypes, ind, val);
    return solutionContainer;
}

/* TODO Check if board is solvable: SolutionContainer to the rescue. */
bool isSolvable(GameState *gameState) {
    UNUSED(gameState);
    return true;
}

SolutionContainer *createSolutionContainer(int size) {
    int i, j, k;
    SolutionContainer *solutionContainer = malloc(sizeof(SolutionContainer));
    solutionContainer->solution = NULL;
    solutionContainer->solutionFound = false;
    solutionContainer->boardSize = size;
    solutionContainer->variables = (int ***) malloc(size * sizeof(int **));
    for (i = 0; i < size; i++) {
        solutionContainer->variables[i] = (int **) malloc(size * sizeof(int *));
        for (j = 0; j < size; j++) {
            solutionContainer->variables[i][j] = (int *) calloc(size, sizeof(int));
            for (k = 0; k < size; k++) {
                solutionContainer->variables[i][j][k] = -1;
            }
        }
    }
    return solutionContainer;
}

void destroySolutionContainer(SolutionContainer *solutionContainer) {
    int i, j;
    if (solutionContainer->solution != NULL) {
        free(solutionContainer->solution);
    }
    for (i = 0; i < solutionContainer->boardSize; i++) {
        for (j = 0; j < solutionContainer->boardSize; j++) {
            free (solutionContainer->variables[i][j]);
        }
        free(solutionContainer->variables[i]);
    }
    free(solutionContainer->variables);
    free(solutionContainer);
}

void destroyGurobi(GRBenv *env, GRBmodel *model, double *obj, char *variableTypes, int *ind, double *val) {
    GRBfreemodel(model);
    GRBfreeenv(env);
    free(obj);
    free(variableTypes);
    free(ind);
    free(val);
}

int getValueFromILPSolution(SolutionContainer* solutionContainer, int row, int col) {
    int value, idx;
    for (value = 1; value <= solutionContainer->boardSize; value++) {
        idx = solutionContainer->variables[row][col][value-1];
        if (idx != -1 && solutionContainer->solution[idx] == 1) {
            return value;
        }
    }
    return -1;
}

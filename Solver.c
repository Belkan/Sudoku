#include <stdlib.h>
#include "gurobi_c.h"
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

Gurobi* getSolution(GameState *gameState, LinearMethod linearMethod) {
    GRBenv *env = NULL;
    GRBmodel *model = NULL;
    int error = 0;
    double* sol = NULL;
    int* ind = malloc(getSize(gameState)* sizeof(int));
    double* val = malloc(getSize(gameState)*sizeof(double));
    double* obj = NULL;
    char* vtype = NULL;
    int optimstatus;
    double objval;
    Gurobi *gurobi = createGurobi(getSize(gameState));


    /* Create environment - log file is gurobi.log */
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {
        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Create an empty model named "sudoku" */
    error = GRBnewmodel(env, &model, "sudoku", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }
    /* Add variables */

    /* coefficients - for x,y,z (cells 0,1,2 in "obj") */
    obj[0] = 1; obj[1] = 3; obj[2] = 2;

    /* variable types - for x,y,z (cells 0,1,2 in "vtype") */
    /* other options: GRB_INTEGER, GRB_CONTINUOUS */
    vtype[0] = GRB_BINARY; vtype[1] = GRB_BINARY; vtype[2] = GRB_BINARY;

    /* add variables to model */
    error = GRBaddvars(model, 3, 0, NULL, NULL, NULL, obj, NULL, NULL, vtype, NULL);
    if (error) {
        printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Change objective sense to maximization */
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* update the model - to integrate new variables */

    error = GRBupdatemodel(model);
    if (error) {
        printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }


    /* First constraint: x + 2 y + 3 z <= 5 */

    /* variables x,y,z (0,1,2) */
    ind[0] = 0; ind[1] = 1; ind[2] = 2;
    /* coefficients (according to variables in "ind") */
    val[0] = 1; val[1] = 2; val[2] = 3;

    /* add constraint to model - note size 3 + operator GRB_LESS_EQUAL */
    /* -- equation value (5.0) + unique constraint name */
    error = GRBaddconstr(model, 3, ind, val, GRB_LESS_EQUAL, 5, "c0");
    if (error) {
        printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Second constraint: x + y >= 1 */
    ind[0] = 0; ind[1] = 1;
    val[0] = 1; val[1] = 1;

    /* add constraint to model - note size 2 + operator GRB_GREATER_EQUAL */
    /* -- equation value (1.0) + unique constraint name */
    error = GRBaddconstr(model, 2, ind, val, GRB_GREATER_EQUAL, 1.0, "c1");
    if (error) {
        printf("ERROR %d 2nd GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Optimize model - need to call this before calculation */
    error = GRBoptimize(model);
    if (error) {
        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Write model to 'mip1.lp' - this is not necessary but very helpful */
    error = GRBwrite(model, "mip1.lp");
    if (error) {
        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* Get solution information */

    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) {
        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* get the objective -- the optimal result of the function */
    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) {
        printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* get the solution - the assignment to each variable */
    /* 3-- number of variables, the size of "sol" should match */
    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, 3, sol);
    if (error) {
        printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
        gurobi->error = error;
        return gurobi;
    }

    /* print results */
    printf("\nOptimization complete\n");

    /* solution found */
    if (optimstatus == GRB_OPTIMAL) {
        printf("Optimal objective: %.4e\n", objval);
        printf("  x=%.2f, y=%.2f, z=%.2f\n", sol[0], sol[1], sol[2]);
    }
        /* no solution found */
    else if (optimstatus == GRB_INF_OR_UNBD) {
        printf("Model is infeasible or unbounded\n");
    }
        /* error or calculation stopped */
    else {
        printf("Optimization was stopped early\n");
    }

    /* IMPORTANT !!! - Free model and environment */
    GRBfreemodel(model);
    GRBfreeenv(env);

    return 0;
}

/* TODO Check if board is solvable: Gurobi to the rescue. */
bool isSolvable(GameState *gameState) {
    UNUSED(gameState);
    return true;
}


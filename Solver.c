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
            }
            else {
                solutions++;
                pop(stack);
                continue;
            }
        }

        /* Attempt to find a legal move for current cell, starting from its current value + 1. */
        for (idx = getCellValue(row, col, gameState, BOARD) + 1; idx <= size; idx++) {
            if (safeMove(row, col, idx, gameState, BOARD)) {
                move = idx;
                foundMove = true;
                break;
            }
        }

        /* Case we have reached the end: attempt all possible values and increment counter. */
        if (reachedEnd) {
            for (idx = 1; idx <= size; idx++) {
                if (safeMove(row, col, idx, gameState, BOARD)) {
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
                setCellValue(row, col, move, gameState, BOARD);
                push(stack, getNextRow(size, row, col), getNextCol(size, col));
                continue;
            }
            else {
                /* Didn't find a move and didn't finish yet. Set cell to 0 and backtrack by popping. */
                setCellValue(row, col, 0, gameState, BOARD);
                pop(stack);
                continue;
            }
        }
    }
    printBoard(gameState, BOARD);
    destroyStack(stack);
    return solutions;
}

/* Checks if there is a solution to the board. Assumes solution is empty. */
bool isSolvableRecursion(GameState *gameState, int row, int col, SOLUTION_TYPE type) {
    int rand, valuesLeft, j, i;
    int k = 0;
    int size = getSize(gameState);
    int* possibleVals = malloc(size * sizeof(int));
    int nextRow = getNextRow(getSize(gameState), row, col);
    int nextCol = getNextCol(getSize(gameState), col);

     /* Stopping condition - filled the entire board.*/
    if (row == getSize(gameState)) {
        free(possibleVals);
        return true;
    }
    /* If empty cell - move to next cell. */
    if (getCellValue(row, col, gameState, SOLUTION) != 0) {
        free(possibleVals);
        return (isSolvableRecursion(gameState, nextRow, nextCol, type));
    }
    /* Find all legal values. */
    for (i = 1; i <= size; i++) {
        if (safeMove(row, col, i, gameState, SOLUTION)) {
            possibleVals[k] = i;
            k++;
        }
    }
    /* No solution for current state - backtrack.*/
    if (k == 0) {
        free(possibleVals);
        return false;
    }
     /* Pick a value (randomly or deterministically) and move to the next cell.*/
    valuesLeft = k;
    switch (type) {
        case (DETERMINISTIC):
            for (i = 0; i < k; i++) {
                setCellValue(row, col, possibleVals[i], gameState, SOLUTION);
                if (isSolvableRecursion(gameState, nextRow, nextCol, DETERMINISTIC)) {
                    free(possibleVals);
                    return true;
                }
            }
            break;
        case (RANDOM):
            for (i = 0; i < k; i++) {
                rand = getRandom(0, --valuesLeft);
                setCellValue(row, col, possibleVals[rand], gameState, SOLUTION);
                 /*Remove the randomly selected value from possibleVals.*/
                possibleVals[rand] = possibleVals[valuesLeft];
                /*Sort the array bubblesortish (requested by HW3 instructions)*/
                for (j = rand; j < valuesLeft - 1; j++) {
                    swap(&possibleVals[j],&possibleVals[j+1]);
                }
                if (isSolvableRecursion(gameState, nextRow, nextCol, RANDOM)) {
                    free(possibleVals);
                    return true;
                }
            }
            break;
    }

     /*No legal values left to pick - backtrack.*/
     setCellValue(row, col, 0, gameState, SOLUTION);
    free(possibleVals);
    return false;
}

/* Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.*/
bool isSolvable(GameState *gameState) {
    GameState* tempGameState = createGameState(getRowsInBlock(gameState), getColsInBlock(gameState));

    copyFromBoardToBoard(gameState, BOARD, tempGameState, SOLUTION);
    if (isSolvableRecursion(tempGameState,0,0,DETERMINISTIC)) {
        copyFromBoardToBoard(tempGameState, SOLUTION, gameState, SOLUTION);
        destroyGameState(tempGameState);
        return true;
    }
    destroyGameState(tempGameState);
    return false;

}

/* Generates the initial random solution. Assumes solution is empty.*/
void generateRandomSolution(GameState *gameState) {
    isSolvableRecursion(gameState, 0, 0, RANDOM);
}


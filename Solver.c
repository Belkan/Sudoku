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
            }
            else {
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


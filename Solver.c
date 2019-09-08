#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"
#include "MainAux.h"

/* Initialize stack of given capacity. */
struct recursion_stack* createStack(int capacity) {
    struct recursion_stack *stack = malloc(sizeof(struct recursion_stack));
    int idx = 0;

    /* Initially, top index is 0. Index of -1 denotes empty stack. */
    stack->top = 0;
    stack->capacity = capacity;
    /* Start with cell [1,1] and set it to value 1, the least value. */
    stack->rows = (int *) malloc(capacity * sizeof(int));
    stack->rows[0] = 0;
    stack->cols = (int *) malloc(capacity * sizeof(int));
    stack->cols[0] = 0;

    /* Set other entries to 0. */
    for (idx = 1; idx < capacity; idx++) {
        stack->rows[idx] = 0;
        stack->cols[idx] = 0;
    }
    return stack;
}

void destroyStack(struct recursion_stack *stack) {
    free(stack->rows);
    free(stack->cols);
    free(stack);
}

/* Check if stack is full (i.e. stack overflow). */
bool isFull(struct recursion_stack *stack) {
    if (stack->top == stack->capacity) return true;
    return false;
}

/* Check if stack is empty. */
bool isEmpty(struct recursion_stack *stack) {
    if (stack->top == -1) return true;
    return false;
}

/* Push new game state to top of the stack. */
bool push(struct recursion_stack *stack, int row, int col) {
    /* Avoid stack overflow. */
    if (isFull(stack)) {
        return false;
    }
    ++stack->top;
    stack->rows[stack->top] = row;
    stack->cols[stack->top] = col;
    return true;
}

/* Removes top element of stack. */
bool pop(struct recursion_stack *stack) {
    /* Avoid stack underflow. */
    if (isEmpty(stack)) {
        return false;
    }
    --stack->top;
    return true;
}

/* TODO compare with Ellie & Nofar num of solutions on various boards to ensure correctness. */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState) {
    bool foundMove = false, reachedEnd = false;
    int row = 0, col = 0, size = getSize(gameState), solutions = 0, idx = 0, move = -1;
    struct recursion_stack *stack = createStack(gameState->size * gameState->size);

    /* Iterating until stack empties replaces recursion. */
    while (!isEmpty(stack)) {
        foundMove = false;
        reachedEnd = false;
        row = stack->rows[stack->top];
        col = stack->cols[stack->top];
        move = -1;

        /* Flag checks if we have reached the end of the board. */
        reachedEnd = (row == size - 1 && col == size - 1);

        /* Avoid fixed cells. */
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

/* Subfunctions for isSolvableRecursion */
int getNextRow(int size, int row, int col) {
    if (col < size - 1) {
        return row;
    } else {
        return row + 1;
    }
}

int getNextCol(int size, int col) {
    if (col < size - 1) {
        return col + 1;
    } else {
        return 0;
    }
}

int getPrevRow(int row, int col) {
    if (col == 0) {
        return row - 1;
    }
    return row;
}

int getPrevCol(int size, int col) {
    if (col == 0) {
        return size - 1;
    }
    return col - 1;
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
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


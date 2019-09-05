#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"
#include "MainAux.h"

/* Initialize stack of given capacity. */
struct recursion_stack* createStack(int capacity) {
    struct recursion_stack *stack = malloc(sizeof(struct recursion_stack));
    int idx = 0;

    stack->top = 1;
    stack->capacity = capacity;
    /* Start with cell [1,1] and set it to value 1, the least value. */
    stack->rows = (int *) malloc(capacity * sizeof(int));
    stack->rows[0] = 0;
    stack->cols = (int *) malloc(capacity * sizeof(int));
    stack->cols[0] = 0;
    stack->vals= (int *) malloc(capacity * sizeof(int));
    stack->vals[0] = 1;

    /* Set other entries to 0. */
    for (idx = 1; idx < capacity; idx++) {
        stack->rows[idx] = 0;
        stack->cols[idx] = 0;
        stack->rows[idx] = 0;
    }
    return stack;
}

void destroyStack(struct recursion_stack *stack) {
    free(stack->rows);
    free(stack->cols);
    free(stack->vals);
    free(stack);
}

/* Check if stack is full (i.e. stack overflow). */
bool isFull(struct recursion_stack *stack) {
    if (stack->top == stack->capacity) return true;
    return false;
}

/* Check if stack is empty. */
bool isEmpty(struct recursion_stack *stack) {
    if (stack->top == 0) return true;
    return false;
}

/* Push new game state to top of the stack. */
bool push(struct recursion_stack *stack, int row, int col, int val) {
    /* Avoid stack overflow. */
    if (isFull(stack)) {
        return false;
    }
    stack->rows[++stack->top] = row;
    stack->cols[stack->top] = col;
    stack->vals[stack->top] = val;
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

/* Retrieves top val element of the stack. */
int peek(struct recursion_stack *stack) {
    if (isEmpty(stack)) return 0;
    return stack->vals[stack->top];
}

/* TODO debug */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState) {
    bool foundMove = false;
    int row = 0, col = 0, size = getSize(gameState), solutions = 0, idx = 0;
    struct recursion_stack *stack = createStack(gameState->size);

    /* Iterating until stack empties replaces recursion. */
    while (!isEmpty(stack)) {
        row = getNextRow(size, row, col);
        col = getNextCol(size, col);
        /* Avoid fixed cells. */
        if (isFixed(row, col, gameState)) continue;
        for (idx = peek(stack); idx < size; idx++) {
            if (safeMove(row, col, idx, gameState, BOARD)) {
                push(stack, row, col, idx);
                /* Reached end of the board, therefore another valid solution was found. Time to backtrack. */
                if (row == size - 1 && col == size - 1) {
                    solutions++;
                    pop(stack);
                }
                foundMove = true;
                break;
            }
            /* No move found, time to backtrack. */
            if (!foundMove) {
                pop(stack);
            }
        }
    }
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


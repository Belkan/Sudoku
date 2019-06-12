#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"


/* checks if there is a solution to the board */

bool isSolvableRecursion(GameState *gameState, int** solutionBoardCopy, int row, int col, SOLUTION_TYPE type) {
    int rand, valuesLeft, j, i;
    int k = 0;
    int* possibleVals = malloc(gameState->size * sizeof(int));
    int nextRow = getNextRow(gameState->size, row, col);
    int nextCol = getNextCol(gameState->size, col);


     /* Stopping condition - filled the entire board.*/
    if (row == gameState->size) {
        free(possibleVals);
        return true;
    }
    /* If empty cell - move to next cell. */
    if (solutionBoardCopy[row][col] != 0) {
        free(possibleVals);
        return (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, type));
    }
    /* Find all legal values. */
    for (i = 1; i < 10; i++) {
        if (safeMove(solutionBoardCopy, row, col, i, gameState->size)) {
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
                solutionBoardCopy[row][col] = possibleVals[i];
                if (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, DETERMINISTIC)) {
                    free(possibleVals);
                    return true;
                }
            }
            break;
        case (RANDOM):
            for (i = 0; i < k; i++) {
                rand = getRandom(0, --valuesLeft);
                solutionBoardCopy[row][col] = possibleVals[rand];
                 /*Remove the randomly selected value from possibleVals.*/
                possibleVals[rand] = possibleVals[valuesLeft];
                /*Sort the array bubblesortish (requested by HW3 instructions)*/
                for (j = rand; j < valuesLeft - 1; j++) {
                    swap(&possibleVals[j],&possibleVals[j+1]);
                }
                if (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, RANDOM)) {
                    free(possibleVals);
                    return true;
                }
            }
            break;
    }

     /*No legal values left to pick - backtrack.*/
    solutionBoardCopy[row][col] = 0;
    free(possibleVals);
    return false;
}

/* Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.*/
bool isSolvable(GameState *gameState) {
    int i;
    int** solutionBoardCopy = (int**) malloc(gameState->size * sizeof(int*));
    for (i = 0; i < gameState->size; i++){
        solutionBoardCopy[i] =  calloc(gameState->size, sizeof(int));
    }

    copyFromBoardToBoard(gameState->board, solutionBoardCopy, gameState->size);
    if (isSolvableRecursion(gameState,solutionBoardCopy,0,0,DETERMINISTIC)) {
        copyFromBoardToBoard(solutionBoardCopy, gameState->solution, gameState->size);
        destroyMatrix(solutionBoardCopy, gameState->size);
        return true;
    }
    destroyMatrix(solutionBoardCopy, gameState->size);
    return false;

}

/* Should only be called after gameState->solution is initialized.*/
void generateRandomSolution(GameState *gameState) {
    isSolvableRecursion(gameState, gameState->solution, 0, 0, RANDOM);
}

/* get next row to traverse to */
int getNextRow(int size, int row, int col) {
    if (col < size - 1) {
        return row;
    } else {
        return row + 1;
    }
}

/* get next col to traverse to */
int getNextCol(int size, int col) {
    if (col < size - 1) {
        return col + 1;
    } else {
        return 0;
    }

}

/* util function to swap values of pointers */
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

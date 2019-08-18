#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"
#include "MainAux.h"


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


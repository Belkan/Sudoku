#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"


/* checks if there is a solution to the board */

bool isSolvableRecursion(GameState *gameState, int **solutionBoardCopy, int row, int col, SOLUTION_TYPE type) {
    int rand, valuesLeft;
    int k = 0;
    int *possibleVals[gameState->size];
    int nextRow = getNextRow(gameState->size, row, col);
    int nextCol = getNextCol(gameState->size, col);

    // If fixed cell = move on.
    // Stopping condition - filled the entire board.
    if (row == gameState->size) {
        return true;
    }
    // Find all legal values.
    for (int i = 1; i < 10; i++) {
        if (safeMove(gameState, row, col, i, SOLUTION)) {
            possibleVals[k] = i;
            k++;
        }
    }
    // No solution for current state - need to backtrack.
    if (k == 0) {
        return false;
    }


    valuesLeft = k;
    switch (type) {
        case (DETERMINISTIC):
            for (int i = 0; i < k; i++) {
                solutionBoardCopy[row][col] = possibleVals[i];
                // Remove the randomly selected value from possibleVals.
                if (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, DETERMINISTIC)) {
                    return true;
                }
            }
        case (RANDOM):
            for (int i = 0; i < k; i++) {
                rand = getRandom(0, valuesLeft - 1);
                solutionBoardCopy[row][col] = possibleVals[rand];
                // Remove the randomly selected value from possibleVals.
                possibleVals[rand] = possibleVals[valuesLeft - 1];
                valuesLeft--;
                if (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, RANDOM)) {
                    return true;
                }
            }
    }

    // No legal value led to a valid solution.
    solutionBoardCopy[row][col] = 0;
    return false;
} /* EOF */

bool isSolvable(GameState *gameState, SOLUTION_TYPE type){
    int** solutionBoardCopy[gameState->size][gameState->size];
    copyFromBoardToBoard(gameState->solution, solutionBoardCopy, gameState->size);
    if (isSolvableRecursion(gameState,solutionBoardCopy,0,0,type)) {
        gameState->solution = solutionBoardCopy;
        return true;
    }
    return false;

}

void generateRandomSolution(GameState *gameState) {
    isSolvableRecursion(gameState, gameState->solution, 0, 0, RANDOM);
}


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
#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"


/* checks if there is a solution to the board */

bool isSolvableRecursion(GameState *gameState, int** solutionBoardCopy, int row, int col, SOLUTION_TYPE type) {
    int rand, valuesLeft;
    int k = 0;
    int possibleVals[gameState->size];
    int nextRow = getNextRow(gameState->size, row, col);
    int nextCol = getNextCol(gameState->size, col);


    // Stopping condition - filled the entire board.
    if (row == gameState->size) {
        return true;
    }
    // If empty cell - move to next cell.
    if (solutionBoardCopy[row][col] != 0) {
        return (isSolvableRecursion(gameState, solutionBoardCopy, nextRow, nextCol, type));
    }
    // Find all legal values.
    for (int i = 1; i < 10; i++) {
        if (safeMove(solutionBoardCopy, row, col, i, gameState->size)) {
            possibleVals[k] = i;
            k++;
        }
    }
    // No solution for current state - backtrack.
    if (k == 0) {
        return false;
    }
    // Pick a value (randomly or deterministically) and move to the next cell.
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
            break;
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
            break;
    }

    // No legal values left to pick - backtrack.
    solutionBoardCopy[row][col] = 0;
    return false;
} /* EOF */

// Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.
bool isSolvable(GameState *gameState) {
    int** solutionBoardCopy = (int**) malloc(gameState->size * sizeof(int*));
    for (int i = 0; i < gameState->size; i++){
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

// Should only be called after gameState->solution is initialized.
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
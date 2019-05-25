#include <stdlib.h>
#include <stdio.h>
#include "Solver.h"


/* generates a random solved board */
bool randomSolution(GameState *gameState, int row, int col) {
    int rand, k, nextRow, nextCol, valuesLeft;
    int *possibleVals = calloc(gameState->size, sizeof(int));
    k = 0;

    // Stopping condition - filled the entire board.
    if (row == gameState->size) {
        free(possibleVals);
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
        free(possibleVals);
        return false;
    }

    nextRow = getNextRow(gameState->size, row, col);
    nextCol = getNextCol(gameState->size, col);
    valuesLeft = k;

    for (int i = 0; i < k; i++) {
        rand = getRandom(0, valuesLeft - 1);
        gameState->solution[row][col] = possibleVals[rand];
        // Remove the randomly selected value from possibleVals.
        possibleVals[rand] = possibleVals[valuesLeft - 1];
        valuesLeft--;
        if (randomSolution(gameState, nextRow, nextCol)) {
            free(possibleVals);
            return true;
        }
    }
    // No legal value led to a valid solution.
    gameState->solution[row][col] = 0;
    free(possibleVals);
    return false;
} /* EOF */

void generateRandomSolution(GameState *gameState) {
    randomSolution(gameState, 0, 0);
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
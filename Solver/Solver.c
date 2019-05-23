#include "Solver.h"

/* generates a random solved board */
/* TODO see this actually generates a random board */
bool generateRandBoard(GameState *gameState, int row, int col) {
    int val, i, k, nextCol, nextRow;
    char possibleVals[8];
    if (countBlanks(gameState, 's') == 0) {
        return true; /* finished placement of all board */
    }

    /* get a random cell to recursively call */
    nextRow = getRandom(0, SIZE - 1);
    nextCol = getRandom(0, SIZE - 1);

    /* a value has already been placed in this location */
    if (gameState->solution[row][col] != 0) {
        return generateRandBoard(gameState, nextRow, nextCol);
    }

    k = 0;
    for (i = 1; i < 10; i++) {
        if (safeMove(gameState, row, col, i, 's')) {
            possibleVals[k] = i;
            k++;
        }
    }

    if (k == 0) {
        /* no legal moves available */
        return false;
    }

    /* choose random value out of possible values */
    i = getRandom(1, k);
    val = possibleVals[i];
    gameState->solution[row][col] = val;

    if (generateRandBoard(gameState, nextRow, nextCol)) {
        return true;
    } else {
        /* unsuccessful value chosen, reset it */
        gameState->solution[row][col] = 0;
    }
    return false;
} /* EOF */
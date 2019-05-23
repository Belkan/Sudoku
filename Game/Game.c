
#include <stdio.h>
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set (GameState *gameState, int row, int col, int value) {
    SET_STATUS Status;
    if (isFixed(row, col, gameState)) {
        Status = CELL_FIXED;
        return Status;
    }
    if (!isLegalMove(gameState, row, col, value)) {
        Status = ILLEGAL_MOVE;
        return Status;
    }

    gameState->board[row][col] = value;
    if (fullBoard(gameState)){
        Status = GAME_OVER;
        return Status;
    }

    Status = SUCCESS;
    return Status;

}
void hint (GameState *gameState, int row, int col){}

void validate (GameState *gameState){}

void restart (GameState *gameState){}

/* TODO: check if it's in the same box (currently only checks row and col */
/* checks if this set is a legal set (assuming input is valid) */
bool isLegalMove(GameState *gameState, int row, int col, int value){
    int i;
    for (i = 0; i < 9; i++){
        if (gameState->board[i][col] == value || gameState->board[row][i] == value) {
            return false;
        }
    }
    return true;
}

/* check if the board is full */
bool fullBoard(GameState *gameState){
    int i, j;
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            if (gameState->board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
} /* EOF */

/* return number of empty cells in board */
int countBlanks(GameState *gameState) {
    int row, col, count;
    for (row = 0; row < gameState->size; row++) {
        for (col = 0; col < gameState->size; col++) {
            if (gameState->solution[row][col] == 0) {
                count++;
            }
        }
    }
    return count;
} /* EOF */

/* checks if placement is legal */
bool safeMove(GameState *gameState, int row, int col, int val) {
    int block = findBlock(row, col);

    return safeMoveRow(gameState, row, val)
           && safeMoveCol(gameState, col, val)
           && safeMoveBlock(gameState, block, val);
} /* EOF */

/* Util subfunctions used for safeMove */
bool safeMoveRow(GameState *gameState, int row, int val) {
    int col;

    for (col = 0; col < gameState->size; col++) {
        if (gameState->solution[row][col] == val)
            return false; /* val exists in row */
    }
    return true;
}
bool safeMoveCol(GameState *gameState, int col, int val) {
    int row;

    for (row = 0; row  < gameState->size; row++) {
        if (gameState->solution[row][col] == val)
            return false; /* val exists in column */
    }
    return true;
}
bool safeMoveBlock(GameState *gameState, int block, int val) {
    int fromRow, fromCol, toRow, toCol, i, j;

    switch (block) {
        case 1:
            fromRow = 0;
            fromCol = 0;
            toRow = BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 2:
            fromRow = 0;
            fromCol = BLOCK;
            toRow = BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 3:
            fromRow = 0;
            fromCol = 2 * BLOCK;
            toRow = BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        case 4:
            fromRow = BLOCK;
            fromCol = 0;
            toRow = 2 * BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 5:
            fromRow = BLOCK;
            fromCol = BLOCK;
            toRow = 2 * BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 6:
            fromRow = BLOCK;
            fromCol = 2 * BLOCK;
            toRow = 2 * BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        case 7:
            fromRow = 2 * BLOCK;
            fromCol = 0;
            toRow = 3 * BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 8:
            fromRow = 2 * BLOCK;
            fromCol = BLOCK;
            toRow = 3 * BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 9:
            fromRow = 2 * BLOCK;
            fromCol = 2 * BLOCK;
            toRow = 3 * BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        default:
            printf("Error: safeMoveBlock has failed\n");
            fromRow = fromCol = toRow = toCol = 0;
            break;
    }

    for (i = fromRow; i <= toRow; i++) {
        for (j = fromCol; j <= toCol; j++) {
            if (gameState->solution[i][j] == val) { /* val exists in block */
                return false;
            }
        }
    }
    return true;
} /* EOF */

int findBlock(int row, int col) {
    if (row >= 0 && row <=  2) {
        if (col >= 0 && col <= 2) {
            return 1;
        }
        if (col >=3 && col <= 5) {
            return 2;
        }
        if (col >= 6 && col <= 8) {
            return 3;
        }
    }
    if (row >= 3 && row <= 5) {
        if (col >= 0 && col <= 2) {
            return 4;
        }
        if (col >=3 && col <= 5) {
            return 5;
        }
        if (col >= 6 && col <= 8) {
            return 6;
        }
    }
    if (row >= 6 && row <= 8) {
        if (col >= 0 && col <= 2) {
            return 7;
        }
        if (col >=3 && col <= 5) {
            return 8;
        }
        if (col >= 6 && col <= 8) {
            return 9;
        }
    }
    printf("Error: findBlock has failed\n");
    return 0;
} /* EOF */

/* generates a solved board with H filled values */
/* TODO see this actually generates a random board */
bool generateRandBoard(GameState *gameState, int row, int col) {
    int val, i, k, nextCol, nextRow;
    char possibleVals [8];
    if (countBlanks(gameState) == 0) {
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
        if (safeMove(gameState, row, col, i)) {
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
    }
    else {
        /* unsuccessful value chosen, reset it */
        gameState->solution[row][col] = 0;
    }
    return false;
} /* EOF */
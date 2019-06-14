
#include <stdio.h>
#include <math.h>
#include "Game.h"
#include "Solver.h"
#include "MainAux.h"

/* Tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value) {
    SET_STATUS Status;
    if (isFixed(row,col,gameState)) {
        Status = CELL_FIXED;
        return Status;
    }
    if (!isUserLegalMove(gameState, row, col, value)) {
        Status = ILLEGAL_MOVE;
        return Status;
    }
    setCellValue(row,col,value,gameState,BOARD);
    if (isUserBoardFull(gameState)) {
        Status = GAME_OVER;
        return Status;
    }

    Status = SUCCESS;
    return Status;

}

/* Gives user hint for next move */
void hint(GameState *gameState, int row, int col) {
    printf("Hint: set cell to %d\n", getCellValue(row,col,gameState,SOLUTION));
}

/* Validates if board is solvable and updates the solution if so. */
bool validate(GameState *gameState) {
    if (isSolvable(gameState)) {
        printf("Validation passed: board is solvable\n");
        return true;
    }
    printf("Validation failed: board is unsolvable\n");
    return false;
    }

/* Checks if this set is a legal set (assuming input is valid i.e. not fixed cell) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value) {
    int oldValue = getCellValue(row, col, gameState, BOARD);
    setCellValue(row, col, 0, gameState, BOARD);
    if (value == 0 || safeMove(row, col, value, gameState, BOARD)) {
        return true;
    }
    setCellValue(row, col, oldValue, gameState, BOARD);
    return false;
}

/* Checks if the board is full */
bool isUserBoardFull(GameState *gameState) {
    if (countBlanks(gameState, BOARD) == 0) {
        return true;
    }
    return false;
}

/* Returns number of empty cells in board */
int countBlanks(GameState *gameState, BOARD_TYPE type) {
    int row, col, count = 0;

    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState, type) == 0) {
                count++;
            }
        }
    }
    return count;
}

/* Checks if placement is legal */
bool safeMove(int row, int col, int val, GameState* gameState, BOARD_TYPE type) {
    int block = findBlock(row, col);

    return safeMoveRow(row, val, gameState, type) &&
           safeMoveCol(col, val, gameState, type) &&
           safeMoveBlock(block, val, gameState, type);
}

/* Util subfunctions used for safeMove */

bool safeMoveRow(int row, int val, GameState* gameState, BOARD_TYPE type) {
    int col;
    for (col = 0; col < getSize(gameState); col++) {
        if (getCellValue(row, col, gameState, type) == val)
            return false; /* val exists in row */
    }
    return true;
}

bool safeMoveCol(int col, int val, GameState* gameState, BOARD_TYPE type) {
    int row;

    for (row = 0; row < getSize(gameState); row++) {
        if (getCellValue(row, col, gameState, type) == val)
            return false; /* val exists in column */
    }
    return true;
}

bool safeMoveBlock(int block, int val, GameState* gameState, BOARD_TYPE type) {
    int blockSize = (int)sqrt(getSize(gameState)), row, col;
    int fromRow = (block / blockSize) * blockSize;
    int fromCol = (block % blockSize) * blockSize;
    for (row = fromRow; row <= fromRow + 2; row++) {
        for (col = fromCol; col <= fromCol + 2; col++) {
            if (getCellValue(row, col, gameState, type) == val) { /* val exists in block */
                return false;
            }
        }
    }
    return true;
}

int findBlock(int row, int col) {
    return ((row / 3)*3 + (col / 3));
}


/* Sets the amount of initial fixed cells for board */
void setFixedCellsRand(GameState *gameState, int fixed) {
    int row, col, counter;
    counter = 0;
    if (fixed == -1){
        printf("Exiting...\n");
        destroyGameState(gameState);
        exit(0);
    }
    while (counter < fixed) {
        col = getRandom(0,8);
        row = getRandom(0,8);
        if (!isFixed(row, col, gameState)) {
            setFixed(row, col, true, gameState);
            counter++;
        }
    }
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (!isFixed(row, col, gameState)) {
                setCellValue(row, col, 0, gameState, BOARD);
            }
        }
    }
}

/* Util function to copy boards */
void copyFromBoardToBoard(GameState* gameStateFrom, BOARD_TYPE fromType, GameState* gameStateTo, BOARD_TYPE toType) {
    int row, col;
    for (row = 0; row < getSize(gameStateFrom); row++){
        for (col = 0; col < getSize(gameStateFrom); col++) {
            setCellValue(row, col, getCellValue(row, col, gameStateFrom, fromType), gameStateTo, toType);
        }
    }
}


/* Handles set status */
void setHandler (SET_STATUS status, GameState *gameState) {
    switch (status) {
        case (SUCCESS):
            printBoard(gameState, BOARD);
            break;
        case (ILLEGAL_MOVE):
            printf("Error: value is invalid\n");
            break;
        case (CELL_FIXED):
            printf("Error: cell is fixed\n");
            break;
        case (GAME_OVER):
            printBoard(gameState,BOARD);
            printf("Puzzle solved successfully\n");
            break;
        default:
            break;
    }
}

/* Getters, setters and general util for GameState */

GameState *createGameState(int size) {
    int i;
    GameState *gameState = malloc(sizeof(GameState));
    gameState->size = size;

    gameState->board = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        gameState->board[i] = calloc(size, sizeof(int));
    }

    gameState->solution = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        gameState->solution[i] = calloc(size, sizeof(int));
    }

    gameState->fixed = (bool **) malloc(size * sizeof(bool *));
    for (i = 0; i < size; i++) {
        gameState->fixed[i] = (bool *) calloc(size, sizeof(bool));
    }

    return gameState;
}

void destroyGameState(GameState *gameState) {
    destroyMatrix(gameState->board, gameState->size);
    destroyMatrix(gameState->solution, gameState->size);
    destroyMatrix((int**) gameState->fixed, gameState->size);
    free(gameState);
}

void setCellValue (int row, int col, int value, GameState* gameState, BOARD_TYPE type) {
    switch (type) {
        case SOLUTION:
            gameState->solution[row][col] = value;
            break;
        default:
            gameState->board[row][col] = value;
    }
}

int getCellValue (int row, int col, GameState* gameState, BOARD_TYPE type) {
    switch (type) {
        case SOLUTION:
            return gameState->solution[row][col];
        default:
            return gameState->board[row][col];
    }
}

void setFixed (int row, int col, bool value, GameState* gameState) {
    gameState->fixed[row][col] = value;
}

bool isFixed (int row, int col, GameState* gameState) {
    return gameState->fixed[row][col];
}

int getSize (GameState* gameState) {
    return gameState->size;
}

#include "MainAux.h"
#include "Solver.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Generates pseudorandom number in given range */
int getRandom(int lower, int upper) {
    int res;
    if (lower == upper) {
        return lower;
    }
    /* randomize result */
    res = (rand() % (upper - lower + 1)) + lower;
    return res;
}

/* Util function to free resources allocated for a matrix */
void destroyMatrix(int **matrix, int size) {
    int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/* Prints the current board */
void printBoard(GameState *gameState, BOARD_TYPE type) {
    int row;
    int col;
    int counter;
    int value;
    int size = getSize(gameState);
    int rowsInBlock = getRowsInBlock(gameState);
    int colsInBlock = getColsInBlock(gameState);

    for (row = 0; row < size; row++) {
        if (row % rowsInBlock == 0) {
            for (counter = 0; counter < (2 * (rowsInBlock) + 1 + size * 4); counter++) {
                printf("-");
            }
            printf("\n");
        }
        for (col = 0; col < size; col++) {
            if (col % colsInBlock == 0) {
                printf("| ");
            }
            value = getCellValue(row, col, gameState, type);
            if (value == 0) {
                printf("    ");
            } else {
                if (value < 10) {
                    printf(" ");
                }
                if (isFixed(row, col, gameState)) {
                    printf(".");
                } else {
                    printf(" ");
                }
                printf("%d ", value);
            }
        }
        printf("|\n");
    }
    for (counter = 0; counter < (2 * (rowsInBlock) + 1 + size * 4); counter++) {
        printf("-");
    }
    printf("\n");
}


/* convert size_t to int */
int size_t2int(size_t val) {
    return (val <= INT_MAX) ? (int) ((ssize_t) val) : -1;
}

/* TODO make START_GAME generic for different statuses, edit/init/solve */
/* Start the game. This is the sole function that should be called from main. */
void START_GAME() {
    /*Initialize*/
    char input[MAX];
    USER_CHOICE status;
    HistoryState *currHistoryState = createHistoryState();
    HistoryState *tmpHistoryState;
    int i = 0;

    /* Empty gamestate in initmode, represents the beginning of the game */
    GameState *gameState = createGameState(1, 1);

    printf("-----------TAUDOKU-----------\n");
    printf("Enter a command of your choice:\n");

/* Start game */
    while (fgets(input, MAX, stdin)) {
        i = 0;
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n') {
            if (input[i] == '\n') {
                break;
            }
            i++;
        }
        if (input[i] == '\n') {
            continue;
        }
        status = parseCommand(gameState, strtok(input, "\n"));

        if (status == EXIT) {
            break;
        } else if (status == UNDO) {
            if (getPreviousState(currHistoryState) == NULL) {
                throw_nothingToUndo();
                break;
            }
            undoMove(currHistoryState, gameState, /* printEnabled= */ true);
            currHistoryState = getPreviousState(currHistoryState);
        } else if (status == REDO) {
            if (getNextState(currHistoryState) == NULL) {
                throw_nothingToRedo();
                break;
            }
            redoMove(currHistoryState, gameState, true);
            currHistoryState = getNextState(currHistoryState);
        } else if (status == RESET) {
            while (getPreviousState(currHistoryState) != NULL) {
                undoMove(currHistoryState, gameState, /* printEnabled= */ false);
                currHistoryState = getPreviousState(currHistoryState);
            }
            printBoard(gameState, BOARD);
        }
            /* Handles all commands other than EXIT or history related. */
        else if (status != INVALID_COMMAND) {
            tmpHistoryState = executeCommand(gameState, status, strtok(input, "\n"));
            if (getChanges(tmpHistoryState) == NULL) {
                destroyHistoryState(tmpHistoryState);
            } else {
                clearForwardHistory(currHistoryState);
                setNextState(currHistoryState, tmpHistoryState);
                setPrevState(tmpHistoryState, currHistoryState);
                currHistoryState = tmpHistoryState;
            }
        }
        checkFullBoard(gameState);
    }

    printf("Exiting...\n");
    destroyGameState(gameState);
    destroyHistoryState(currHistoryState);
    exit(EXIT_SUCCESS);
}


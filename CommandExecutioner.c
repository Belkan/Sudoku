#include "CommandExecutioner.h"
#include "ErrorHandler.h"


void executeSet(GameState *gameState, HistoryState **pHistoryState, int row, int col, int val) {
    HistoryChange *historyChange;
    HistoryState *tmpHistoryState;
    int oldVal = getCellValue(row, col, gameState);
    SET_STATUS status = set(gameState, row, col, val);
    if (status == CELL_FIXED) {
        printf("This cell is fixed, please try again.\n");
        return;
    }
    tmpHistoryState = createHistoryState();
    historyChange = createHistoryChange(row, col, oldVal, val);
    setChanges(tmpHistoryState, historyChange);
    setNextState(*pHistoryState, tmpHistoryState);
    setPrevState(tmpHistoryState, *pHistoryState);
    *pHistoryState = tmpHistoryState;
    printBoard(gameState);
}

void executeEdit(GameState **gameState, HistoryState **pHistoryState, char *filePath, bool hasPath) {
    destroyGameState(*gameState);
    if (hasPath) {
        *gameState = loadFromFile(filePath);
    } else {
        *gameState = loadEmptyBoard();
    }
    setGameMode(*gameState, EDITMODE);
    destroyAllHistory(*pHistoryState);
    *pHistoryState = createHistoryState();
    printBoard(*gameState);
}

void executeSolve(GameState **gameState, HistoryState **pHistoryState, char *filePath) {
    destroyGameState(*gameState);
    *gameState = loadFromFile(filePath);
    setGameMode(*gameState, SOLVEMODE);
    destroyAllHistory(*pHistoryState);
    *pHistoryState = createHistoryState();
    printBoard(*gameState);
}

void executeSave(GameState *gameState, char *filePath) {
    saveToFile(filePath, gameState);
    printf("Filed saved successfully.\n");
}

void executeUndo(GameState *gameState, HistoryState **pHistoryState) {
    if (getPreviousState(*pHistoryState) == NULL) {
        throw_nothingToUndo();
        return;
    }
    undoMove(*pHistoryState, gameState, /* printEnabled= */ true);
    *pHistoryState = getPreviousState(*pHistoryState);
    printBoard(gameState);
}

void executeRedo(GameState *gameState, HistoryState **pHistoryState) {
    if (getNextState(*pHistoryState) == NULL) {
        throw_nothingToRedo();
        return;
    }
    redoMove(*pHistoryState, gameState, /* printEnabled= */ true);
    *pHistoryState = getNextState(*pHistoryState);
    printBoard(gameState);
}

void executeReset(GameState *gameState, HistoryState **pHistoryState) {
    while (getPreviousState(*pHistoryState) != NULL) {
        undoMove(*pHistoryState, gameState, /* printEnabled= */ false);
        *pHistoryState = getPreviousState(*pHistoryState);
    }
    printBoard(gameState);
}

void executeAutofill(GameState *gameState, HistoryState **pHistoryState) {
    int row, col, val, singleVal, counter;
    HistoryState *historyState;
    HistoryChange *tmpHistoryChange;
    HistoryChange *historyChange = NULL;
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) == 0) {
                counter = 0;
                for (val = 1; val <= getSize(gameState); val++) {
                    if (safeMove(row, col, val, gameState)) {
                        counter++;
                        singleVal = val;
                        if (counter == 2) {
                            continue;
                        }
                    }
                }
                /* Check if there's only 1 legal value for this empty cell. */
                if (counter == 1) {
                    if (historyChange == NULL) {
                        historyChange = createHistoryChange(row, col, 0, singleVal);
                        tmpHistoryChange = historyChange;
                    } else {
                        tmpHistoryChange->nextChange = createHistoryChange(row, col, 0, singleVal);
                        tmpHistoryChange = tmpHistoryChange->nextChange;
                    }
                }
            }
        }
    }
    if (historyChange != NULL) {
        historyState = createHistoryState();
        setChanges(historyState, historyChange);
        setPrevState(historyState, *pHistoryState);
        setNextState(*pHistoryState, historyState);
        *pHistoryState = historyState;
        /* This is the part that actually writes the filled values to the board */
        redoMove(getPreviousState(*pHistoryState), gameState, /* printEnabled= */ true);
    }
}

void executeNumSolutions (GameState* gameState) {
    printf("The number of possible solutions to this board is: %d.\n", solutionCounter(gameState));
}

void executeValidate (GameState* gameState) {
    SolutionContainer* solutionContainer =  getSolution(gameState, ILP);
    if (solutionContainer->solutionFound) {
        printf("The board is solvable.\n");
    } else {
        printf("The board is unsolvable.\n");
    }
    destroySolutionContainer(solutionContainer, getSize(gameState));
}

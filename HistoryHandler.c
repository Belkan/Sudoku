
#include "HistoryHandler.h"

HistoryState *createHistoryState() {
    HistoryState *historyList = malloc(sizeof(HistoryState));
    historyList->changes = NULL;
    historyList->nextState = NULL;
    historyList->prevState = NULL;
    return historyList;
}

HistoryChange *createHistoryChange(int row, int col, int oldCellValue, int newCellValue) {
    HistoryChange *historyChange = malloc(sizeof(HistoryChange));
    historyChange->row = row;
    historyChange->col = col;
    historyChange->oldCellValue = oldCellValue;
    historyChange->newCellValue = newCellValue;
    historyChange->nextChange = NULL;
    return historyChange;
}

void destroyHistoryState(HistoryState *historyState) {
    if (historyState->changes != NULL) {
        destroyAllChanges(historyState->changes);
    }
    free(historyState);
}

void destroyAllHistory(HistoryState *historyState) {
    HistoryState *tmp = historyState;
    while (historyState->nextState != NULL) {
        historyState = historyState->nextState;
    }
    while (historyState->prevState != NULL) {
        tmp = historyState->prevState;
        destroyHistoryState(historyState);
        historyState = tmp;
    }
    destroyHistoryState(historyState);
}

void destroyAllChanges(HistoryChange *historyChange) {
    HistoryChange *tmp = historyChange;
    while (historyChange->nextChange != NULL) {
        tmp = historyChange->nextChange;
        free(historyChange);
        historyChange = tmp;
    }
    free(historyChange);
}

HistoryState *getNextState(HistoryState *historyState) {
    return historyState->nextState;
}

void setNextState(HistoryState *historyState, HistoryState *nextState) {
    historyState->nextState = nextState;
}

HistoryState *getPreviousState(HistoryState *historyState) {
    return historyState->prevState;
}

void setPrevState(HistoryState *historyState, HistoryState *prevState) {
    historyState->prevState = prevState;
}

HistoryChange *getChanges(HistoryState *historyState) {
    return historyState->changes;
}

void setChanges(HistoryState *historyState, HistoryChange *historyChange) {
    historyState->changes = historyChange;
}

void clearForwardHistory(HistoryState *historyState) {
    HistoryState *tmp;
    if (historyState->nextState == NULL) {
        return;
    }
    while (historyState->nextState != NULL) {
        tmp = historyState->nextState;
        destroyHistoryState(historyState);
        historyState = tmp;
    }

}

void undoMove(HistoryState *historyState, GameState *gameState, bool printEnabled) {
    HistoryChange *changes = getChanges(historyState);
    int row, col, oldVal, newVal;
    while (changes != NULL) {
        row = changes->row;
        col = changes->col;
        newVal = changes->oldCellValue;
        oldVal = changes->newCellValue;
        setCellValue(row, col, newVal, gameState, BOARD);
        if (printEnabled) {
            printf("Cell [%d,%d] changed from %d to %d.\n", row + 1, col + 1, oldVal, newVal);
        }
        changes = changes->nextChange;
    }
}

/* TODO had to put unused attribute for printEnabled in order to build, remove in future release. */
void redoMove(HistoryState *historyState, GameState *gameState, __attribute__ ((unused)) bool printEnabled) {
    HistoryChange *changes = getChanges(getNextState(historyState));
    int row, col, oldVal, newVal;
    while (changes != NULL) {
        row = changes->row;
        col = changes->col;
        newVal = changes->newCellValue;
        oldVal = changes->oldCellValue;
        setCellValue(row, col, newVal, gameState, BOARD);
        if (printEnabled) {
            printf("Cell [%d,%d] changed from %d to %d.\n", row + 1, col + 1, oldVal, newVal);
        }
        changes = changes->nextChange;
    }
}


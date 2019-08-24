
#include "HistoryHandler.h"

HistoryState* createHistoryState() {
    HistoryState *historyList = malloc(sizeof(HistoryState));
    historyList->changes = NULL;
    historyList->nextState = NULL;
    historyList->prevState = NULL;
    return historyList;
}

HistoryChange* createHistoryChange(int row, int col, int oldCellValue, int newCellValue) {
    HistoryChange *historyChange = malloc(sizeof(HistoryChange));
    historyChange->row = row;
    historyChange->col = col;
    historyChange->oldCellValue = oldCellValue;
    historyChange->newCellValue = newCellValue;
    historyChange->nextChange = NULL;
    return historyChange;
}

HistoryState* getNextState(HistoryState* historyState) {
    return historyState->nextState;
}

HistoryState* getPreviousState(HistoryState* historyState) {
    return historyState->prevState;
}

HistoryChange* getChanges(HistoryState* historyState) {
    return historyState->changes;
}

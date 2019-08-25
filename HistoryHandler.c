
#include "HistoryHandler.h"

HistoryState* createHistoryState(CHANGE_STATUS status) {
    HistoryState *historyList = malloc(sizeof(HistoryState));
    historyList->changes = NULL;
    historyList->changeStatus = status;
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

void destroyHistoryState(HistoryState* historyState) {
    if (historyState->changes != NULL) {
        destroyAllChanges(historyState->changes);
    }
    free(historyState);
}

void destroyAllHistory(HistoryState* historyState) {
    HistoryState* tmp = historyState;
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

void destroyAllChanges(HistoryChange* historyChange){
    HistoryChange* tmp = historyChange;
    while (historyChange->nextChange != NULL) {
        tmp = historyChange->nextChange;
        free(historyChange);
        historyChange = tmp;
    }
    free(historyChange);
}

HistoryState* getNextState(HistoryState* historyState) {
    return historyState->nextState;
}

void setNextState(HistoryState* historyState, HistoryState* nextState) {
    historyState->nextState = nextState;
}

HistoryState* getPreviousState(HistoryState* historyState) {
    return historyState->prevState;
}

void setPrevState(HistoryState* historyState, HistoryState* prevState) {
    historyState->prevState = prevState;
}

HistoryChange* getChanges(HistoryState* historyState) {
    return historyState->changes;
}

void setChanges(HistoryState* historyState, HistoryChange* historyChange) {
    historyState->changes = historyChange;
}

void clearForwardHistory(HistoryState* historyState) {
    HistoryState* tmp = historyState;
    while (historyState->nextState != NULL) {
        tmp = historyState->nextState;
        destroyHistoryState(historyState);
        historyState = tmp;
    }
    destroyHistoryState(historyState);
}
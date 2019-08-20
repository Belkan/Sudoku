
#include "HistoryHandler.h"

HistoryState* createHistoryState (GameState* gameState) {
    HistoryState *historyState = malloc(sizeof(HistoryState));
    historyState->prev = NULL;
    historyState->next = NULL;
    historyState->gameState = gameState;
    return historyState;
}

void destoryHistoryState (HistoryState* historyState) {
    free(historyState);
}

void setNextState (HistoryState* historyState, HistoryState* nextState) {
    if (getNextState(historyState) != NULL) {
        destoryHistoryState(getNextState(historyState));
    }
    historyState->next = nextState;
}

HistoryState* getNextState (HistoryState* historyState) {
    return historyState->next;
}

void setPrevState (HistoryState* historyState, HistoryState* prevState) {
    if (getPrevState(historyState) != NULL) {
        destoryHistoryState(getPrevState(historyState));
    }
    historyState->prev = prevState;
}

HistoryState* getPrevState (HistoryState* historyState) {
    return historyState->prev;
}



#include "HistoryHandler.h"

HistoryState* createHistoryState (GameState* gameState) {
    HistoryState *historyState = malloc(sizeof(HistoryState));
    historyState->prev = NULL;
    historyState->next = NULL;
    historyState->gameState = gameState;
    return historyState;
}

void deleteAllHistory (HistoryState* historyState) {
    HistoryState* tmpState;
    while (historyState->next != NULL) {
        historyState = historyState->next;
    }
    tmpState = historyState;
    while (tmpState->prev != NULL) {
        tmpState = tmpState->prev;
        free(historyState);
        historyState = tmpState;
    }
    free(tmpState);
}

HistoryState* getNextHistoryState(HistoryState* historyState) {
    return historyState->next;
}

HistoryState* getPreviousHistoryState(HistoryState* historyState) {
    return historyState->prev;
}

GameState* getGameStateFromHistory(HistoryState* historyState) {
    return historyState->gameState;
}

HistoryState* advanceHistoryByGameState (HistoryState* historyState, GameState* gameState) {
    HistoryState* newHistoryState = createHistoryState(gameState);
    newHistoryState->prev = historyState;
    historyState->next = newHistoryState;
    return newHistoryState;
}

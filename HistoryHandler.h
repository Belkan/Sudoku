
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include "Game.h"

typedef struct HistoryState {
    struct HistoryChange* changes;
    struct HistoryState* nextState;
    struct HistoryState* prevState;
} HistoryState;

typedef struct HistoryChange {
    int row;
    int col;
    int oldCellValue;
    int newCellValue;
    struct HistoryChange* nextChange;
} HistoryChange;

HistoryState* createHistoryState (GameState* gameState);

HistoryState* getNextState(HistoryState* historyState);

HistoryState* getPreviousState(HistoryState* historyState);

HistoryChange* getChanges(HistoryState* historyState);

#endif

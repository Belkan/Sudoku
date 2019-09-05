
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include <stdlib.h>
#include "Game.h"
typedef enum change_status {
    DO_SAVE,
    DO_NOT_SAVE
} CHANGE_STATUS ;

typedef struct HistoryChange {
    int row;
    int col;
    int oldCellValue;
    int newCellValue;
    struct HistoryChange* nextChange;
} HistoryChange;

typedef struct HistoryState {
    HistoryChange* changes;
    CHANGE_STATUS changeStatus;
    struct HistoryState* nextState;
    struct HistoryState* prevState;
} HistoryState;

HistoryState* createHistoryState ();

void destroyHistoryState(HistoryState* historyState);

void destroyAllHistory(HistoryState* historyState);

void destroyAllChanges(HistoryChange* historyChange);

HistoryChange* createHistoryChange(int row, int col, int oldCellValue, int newCellValue);

HistoryState* getNextState(HistoryState* historyState);

void setNextState(HistoryState* historyState, HistoryState* nextState);

HistoryState* getPreviousState(HistoryState* historyState);

void setPrevState(HistoryState* historyState, HistoryState* prevState);

HistoryChange* getChanges(HistoryState* historyState);

CHANGE_STATUS getChangeStatus(HistoryState* historyState);

void setChanges(HistoryState* historyState, HistoryChange* historyChange);

void clearForwardHistory(HistoryState* historyState);

void undoMove(HistoryState *historyState, GameState *gameState, bool printEnabled);

void redoMove(HistoryState* historyState, GameState* gameState, __attribute__ ((unused)) bool printEnabled);

#endif

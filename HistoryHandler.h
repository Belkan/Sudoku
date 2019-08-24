
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include <stdlib.h>
typedef enum change_status {
    DO_SAVE,
    DO_NOT_SAVE
} CHANGE_STATUS ;

typedef struct history_change {
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

HistoryChange* createHistoryChange(int row, int col, int oldCellValue, int newCellValue);

HistoryState* getNextState(HistoryState* historyState);

HistoryState* getPreviousState(HistoryState* historyState);

HistoryChange* getChanges(HistoryState* historyState);

CHANGE_STATUS getChangeStatus(HistoryState* historyState);

void setChanges(HistoryState* historyState, HistoryChange* historyChange);

#endif

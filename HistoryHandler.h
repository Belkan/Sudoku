
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include <stdlib.h>
typedef enum change_status {
    SUCCESS_CHANGED,
    SUCCESS_UNCHANGED,
    FAILED
} CHANGE_STATUS ;

typedef struct HistoryState {
    struct HistoryChange* changes;
    CHANGE_STATUS changeStatus;
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



HistoryState* createHistoryState ();

HistoryState* getNextState(HistoryState* historyState);

HistoryState* getPreviousState(HistoryState* historyState);

HistoryChange* getChanges(HistoryState* historyState);

#endif


#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include "Game.h"

typedef struct HistoryState {
    GameState* gameState;
    struct HistoryState* next;
    struct HistoryState* prev;
} HistoryState;

HistoryState* createHistoryState (GameState* gameState);

void destoryHistoryState (HistoryState* historyState);

void setNextState (HistoryState* historyState, HistoryState* nextState);

HistoryState* getNextState (HistoryState*);

void setPrevState (HistoryState* historyState, HistoryState* prevState);

HistoryState* getPrevState (HistoryState*);





#endif

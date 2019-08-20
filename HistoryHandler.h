
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include "Game.h"

typedef struct HistoryState {
    GameState* gameState;
    struct HistoryState* next;
    struct HistoryState* prev;
} HistoryState;

GameState* createHistoryState (GameState* gameState);

HistoryState* setNextState (HistoryState*, HistoryState*);

HistoryState* getNextState (HistoryState*);

HistoryState* setPrevState (HistoryState*, HistoryState*);

HistoryState* getPrevState (HistoryState*);





#endif

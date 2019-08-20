
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include "Game.h"

typedef struct HistoryState {
    GameState* gameState;
    struct HistoryState* next;
    struct HistoryState* prev;
} HistoryState;

HistoryState* createHistoryState (GameState* gameState);

HistoryState* getNextHistoryState(HistoryState* historyState);

HistoryState* getPreviousHistoryState(HistoryState* historyState);

GameState* getGameStateFromHistory(HistoryState* historyState);

/* Will delete all HistoryStates in this historyState's doubly-linked list. */
void deleteAllHistory (HistoryState* historyState);

/* Returns a new HistoryState of gameState that succeeds historyState. */
/* @pre: historyState.next != NULL */
HistoryState* advanceHistoryByGameState (HistoryState* historyState, GameState* gameState);


#endif

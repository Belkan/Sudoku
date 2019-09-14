
#ifndef SUDOKU_HISTORYHANDLER_H
#define SUDOKU_HISTORYHANDLER_H
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

/* This module handles the history of the board, and enables us to redo/undo a move made by user. */

/* Struct represents changes that occurred in the board, nested within HistoryState. */
typedef struct HistoryChange {
    int row;
    int col;
    int oldCellValue;
    int newCellValue;
    struct HistoryChange* nextChange;
} HistoryChange;

/* Struct represents historical state of board, including previous moves and changes occurred. */
typedef struct HistoryState {
    HistoryChange* changes;
    struct HistoryState* nextState;
    struct HistoryState* prevState;
} HistoryState;

/* This function clears all forward history. */
void clearForwardHistory(HistoryState* historyState);

/* This function undoes a move performed by user. */
void undoMove(HistoryState *historyState, GameState *gameState, bool printEnabled);

/* This function redoes a move performed by user. */
void redoMove(HistoryState* historyState, GameState* gameState, __attribute__ ((unused)) bool printEnabled);

/* Getters, setters and creators/destroyers for the structs we have declared */
HistoryState* createHistoryState ();
HistoryChange* createHistoryChange(int row, int col, int oldCellValue, int newCellValue);
void destroyHistoryState(HistoryState* historyState);
void destroyAllHistory(HistoryState* historyState);
void destroyAllChanges(HistoryChange* historyChange);
HistoryState* getNextState(HistoryState* historyState);
HistoryState* getPreviousState(HistoryState* historyState);
HistoryChange* getChanges(HistoryState* historyState);
void setNextState(HistoryState* historyState, HistoryState* nextState);
void setPrevState(HistoryState* historyState, HistoryState* prevState);
void setChanges(HistoryState* historyState, HistoryChange* historyChange);

#endif

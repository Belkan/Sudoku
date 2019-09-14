
#ifndef SUDOKU_COMMANDEXECUTIONER_H
#define SUDOKU_COMMANDEXECUTIONER_H

#include "HistoryHandler.h"
#include "MainAux.h"
#include "FileHandler.h"
#include "Solver.h"

/*  This module responsible for executing the input command, after having identified which command it is. */

/* Enum to represent the available commands made by the user. */
typedef enum user_choice {
    SET,
    HINT,
    VALIDATE,
    RESET,
    EXIT,
    INVALID_COMMAND,
    SOLVE,
    EDIT,
    MARK_ERRORS,
    PRINT_BOARD,
    GUESS,
    GENERATE,
    UNDO,
    REDO,
    SAVE,
    GUESS_HINT,
    NUM_SOLUTIONS,
    AUTOFILL
} USER_CHOICE;

/* Execute various types of commands. */
void executeSet(GameState* gameState, HistoryState** historyState, int row, int col, int val);
void executeEdit(GameState** gameState, HistoryState** historyState, char* filePath, bool hasPath);
void executeSolve(GameState** gameState, HistoryState** historyState, char* filePath);
void executeSave(GameState* gameState, char* filePath);
void executeUndo(GameState* gameState, HistoryState** pHistoryState);
void executeRedo(GameState* gameState, HistoryState** pHistoryState);
void executeReset(GameState* gameState, HistoryState** pHistoryState);
void executeAutofill(GameState *gameState, HistoryState **pHistoryState);
void executeNumSolutions (GameState* gameState);
void executeValidate (GameState* gameState);
void executeHint (GameState* gameState, int row, int col);
void executeGuessHint (GameState* gameState, int row, int col);
void executeGuess(GameState *gameState, HistoryState **pHistoryState, float threshold);
void executeGenerate(GameState *gameState, HistoryState **pHistoryState, int toFill, int toClear);

#endif

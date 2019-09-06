#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#include <stdbool.h>
#include "Game.h"
#include "FileHandler.h"
#include "ErrorHandler.h"
#include "HistoryHandler.h"
#include "ParserUtils.h"
#define MAX 1024



/* Checks if user input matches given regular expressions */
bool matchesFormat(char* str, USER_CHOICE choice);

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState **gameState, char *input);

void executeCommand(GameState **pGameState, HistoryState** pHistoryState, USER_CHOICE commandType, char *input);

#endif


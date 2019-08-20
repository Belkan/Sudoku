
#include "HistoryHandler.h"

GameState* createHistoryState (GameState* gameState);

HistoryState* setNextState (HistoryState*, HistoryState*);

HistoryState* getNextState (HistoryState*);

HistoryState* setPrevState (HistoryState*, HistoryState*);

HistoryState* getPrevState (HistoryState*);
#include "CommandExecutioner.h"
#include "ErrorHandler.h"


void executeSet(GameState *gameState, HistoryState **pHistoryState, int row, int col, int val) {
    HistoryChange *historyChange;
    HistoryState *tmpHistoryState;
    int oldVal = getCellValue(row, col, gameState);
    SET_STATUS status = set(gameState, row, col, val);
    if (status == CELL_FIXED) {
        printf("This cell is fixed, please try again.\n");
        return;
    }
    clearForwardHistory(*pHistoryState);
    tmpHistoryState = createHistoryState();
    historyChange = createHistoryChange(row, col, oldVal, val);
    setChanges(tmpHistoryState, historyChange);
    setNextState(*pHistoryState, tmpHistoryState);
    setPrevState(tmpHistoryState, *pHistoryState);
    *pHistoryState = tmpHistoryState;
    printBoard(gameState);
}

void executeEdit(GameState **gameState, HistoryState **pHistoryState, char *filePath, bool hasPath) {
    destroyGameState(*gameState);
    if (hasPath) {
        *gameState = loadFromFile(filePath);
    } else {
        *gameState = loadEmptyBoard();
    }
    setGameMode(*gameState, EDITMODE);
    destroyAllHistory(*pHistoryState);
    *pHistoryState = createHistoryState();
    printBoard(*gameState);
}

void executeSolve(GameState **gameState, HistoryState **pHistoryState, char *filePath) {
    destroyGameState(*gameState);
    *gameState = loadFromFile(filePath);
    setGameMode(*gameState, SOLVEMODE);
    destroyAllHistory(*pHistoryState);
    *pHistoryState = createHistoryState();
    printBoard(*gameState);
}

void executeSave(GameState *gameState, char *filePath) {
    saveToFile(filePath, gameState);
    printf("Filed saved successfully.\n");
}

void executeUndo(GameState *gameState, HistoryState **pHistoryState) {
    if (getPreviousState(*pHistoryState) == NULL) {
        throw_nothingToUndo();
        return;
    }
    undoMove(*pHistoryState, gameState, /* printEnabled= */ true);
    *pHistoryState = getPreviousState(*pHistoryState);
    printBoard(gameState);
}

void executeRedo(GameState *gameState, HistoryState **pHistoryState) {
    if (getNextState(*pHistoryState) == NULL) {
        throw_nothingToRedo();
        return;
    }
    redoMove(*pHistoryState, gameState, /* printEnabled= */ true);
    *pHistoryState = getNextState(*pHistoryState);
    printBoard(gameState);
}

void executeReset(GameState *gameState, HistoryState **pHistoryState) {
    while (getPreviousState(*pHistoryState) != NULL) {
        undoMove(*pHistoryState, gameState, /* printEnabled= */ false);
        *pHistoryState = getPreviousState(*pHistoryState);
    }
    printBoard(gameState);
}

void executeAutofill(GameState *gameState, HistoryState **pHistoryState) {
    int row, col, val, singleVal, counter;
    HistoryState *historyState;
    HistoryChange *tmpHistoryChange;
    HistoryChange *historyChange = NULL;
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) == 0) {
                counter = 0;
                for (val = 1; val <= getSize(gameState); val++) {
                    if (safeMove(row, col, val, gameState)) {
                        counter++;
                        singleVal = val;
                        if (counter == 2) {
                            continue;
                        }
                    }
                }
                /* Check if there's only 1 legal value for this empty cell. */
                if (counter == 1) {
                    if (historyChange == NULL) {
                        historyChange = createHistoryChange(row, col, 0, singleVal);
                        tmpHistoryChange = historyChange;
                    } else {
                        tmpHistoryChange->nextChange = createHistoryChange(row, col, 0, singleVal);
                        tmpHistoryChange = tmpHistoryChange->nextChange;
                    }
                }
            }
        }
    }
    if (historyChange != NULL) {
        clearForwardHistory(*pHistoryState);
        historyState = createHistoryState();
        setChanges(historyState, historyChange);
        setPrevState(historyState, *pHistoryState);
        setNextState(*pHistoryState, historyState);
        *pHistoryState = historyState;
        /* This is the part that actually writes the filled values to the board */
        redoMove(getPreviousState(*pHistoryState), gameState, /* printEnabled= */ true);
    }
}

void executeNumSolutions(GameState *gameState) {
    printf("The number of possible solutions to this board is: %d.\n", solutionCounter(gameState));
}

void executeValidate(GameState *gameState) {
    SolutionContainer *solutionContainer = getSolution(gameState, ILP);
    if (solutionContainer->solutionFound) {
        printf("The board is solvable.\n");
    } else {
        throw_boardUnsolvable();
    }
    destroySolutionContainer(solutionContainer);
}

void executeHint(GameState *gameState, int row, int col) {
    SolutionContainer *solutionContainer = getSolution(gameState, ILP);
    if (!solutionContainer->solutionFound) {
        throw_boardUnsolvable();
        destroySolutionContainer(solutionContainer);
        return;
    }
    printf("Hint: Fill cell [%d,%d] with value %d.\n", row + 1, col + 1,
           getValueFromILPSolution(solutionContainer, row, col));
    destroySolutionContainer(solutionContainer);
}

void executeGuessHint(GameState *gameState, int row, int col) {
    int value, idx;
    SolutionContainer *solutionContainer = getSolution(gameState, LP);
    if (!solutionContainer->solutionFound) {
        throw_boardUnsolvable();
        destroySolutionContainer(solutionContainer);
        return;
    }
    printf("Possible values for [%d,%d] are:\n", row + 1, col + 1);
    for (value = 1; value <= solutionContainer->boardSize; value++) {
        idx = getIndexOfVariable(solutionContainer, row, col, value);
        if (idx != -1 && solutionContainer->solution[idx] > 0) {
            printf("%d with a score of %.2f.\n", value, solutionContainer->solution[idx]);
        }
    }
    destroySolutionContainer(solutionContainer);
}


void executeGuess(GameState *gameState, HistoryState **pHistoryState, float threshold) {
    int row, col, value, idx, randomVal, legalValsCount;
    double randomDouble;
    double *legalVals;
    double sum;
    HistoryState *historyState;
    HistoryChange *tmpHistoryChange;
    HistoryChange *historyChange = NULL;
    SolutionContainer *solutionContainer = getSolution(gameState, LP);
    if (!solutionContainer->solutionFound) {
        throw_boardUnsolvable();
        destroySolutionContainer(solutionContainer);
        return;
    }
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) == 0) {
                legalValsCount = 0;
                legalVals = calloc(getSize(gameState), sizeof(double));
                for (value = 1; value <= getSize(gameState); value++) {
                    idx = getIndexOfVariable(solutionContainer, row, col, value);
                    if (idx != -1 && solutionContainer->solution[idx] > threshold &&
                        isUserLegalMove(gameState, row, col, value)) {
                        legalVals[value - 1] = solutionContainer->solution[idx];
                        legalValsCount++;
                        printf("%.2f ", solutionContainer->solution[idx]);
                    }
                }
                if (legalValsCount == 0) {
                    free(legalVals);
                    continue;
                }
                printf("\n");
                /* Normalize the values in intervals such that each interval is in the size of the probability. */
                sum = 0.0;
                for (value = 1; value <= getSize(gameState); value++) {
                    sum += legalVals[value - 1];
                    legalVals[value - 1] = sum;
                    printf("%.2f ", legalVals[value - 1]);
                }
                printf("\n\n");
                /* Randomize a double between 0 and sum. */
                randomDouble = (rand() / (double) RAND_MAX) * sum;
                /* Pick the selected number. */
                for (value = 1; value <= getSize(gameState); value++) {
                    if (randomDouble <= legalVals[value - 1]) {
                        randomVal = value;
                        break;
                    }
                }
                /* Set the selected number. */
                setCellValue(row, col, randomVal, gameState);
                if (historyChange == NULL) {
                    historyChange = createHistoryChange(row, col, 0, randomVal);
                    tmpHistoryChange = historyChange;
                } else {
                    tmpHistoryChange->nextChange = createHistoryChange(row, col, 0, randomVal);
                    tmpHistoryChange = tmpHistoryChange->nextChange;
                }

                free(legalVals);
            }
        }
    }
    if (historyChange != NULL) {
        clearForwardHistory(*pHistoryState);
        historyState = createHistoryState();
        setChanges(historyState, historyChange);
        setPrevState(historyState, *pHistoryState);
        setNextState(*pHistoryState, historyState);
        *pHistoryState = historyState;
        printBoard(gameState);
    }
}

void executeGenerate(GameState *gameState, HistoryState **pHistoryState, int toFill, int cellsLeft) {
    HistoryState *historyState;
    HistoryChange *tmpHistoryChange;
    HistoryChange *historyChange = NULL;
    SolutionContainer *solutionContainer;
    int attempt = 0, cleared = 0;
    int row, col, value, filled, legalValuesCount, randomVal, idx;
    int toClear = getSize(gameState)*getSize(gameState) - cellsLeft;
    int *legalValues;
    bool attemptSuccessful;
    GameState *cpyGameState;

    while (attempt < 1000) {
        /* Initialize */
        filled = 0;
        attemptSuccessful = true;
        cpyGameState = createGameState(getRowsInBlock(gameState), getColsInBlock(gameState));
        copyFromBoardToBoard(gameState, cpyGameState);
        /* Attempt to fill cells randomly */
        while (filled < toFill) {
            row = getRandom(0, getSize(cpyGameState) - 1);
            col = getRandom(0, getSize(cpyGameState) - 1);
            if (getCellValue(row, col, cpyGameState) != 0) {
                continue;
            }
            legalValues = malloc(getSize(cpyGameState) * sizeof(int));
            legalValuesCount = 0;
            for (value = 1; value <= getSize(cpyGameState); value++) {
                if (isUserLegalMove(gameState, row, col, value)) {
                    legalValues[legalValuesCount++] = value;
                }
            }
            if (legalValuesCount == 0) {
                attemptSuccessful = false;
                free(legalValues);
                break;
            }
            randomVal = legalValues[getRandom(0, legalValuesCount - 1)];
            setCellValue(row, col, randomVal, cpyGameState);
            filled++;
            free(legalValues);
        }
        if (!attemptSuccessful) {
            attempt++;
            destroyGameState(cpyGameState);
            continue;
        }
        /* Attempt to solve the remaining board using ILP */
        solutionContainer = getSolution(cpyGameState, ILP);
        if (!solutionContainer->solutionFound) {
            attempt++;
            destroyGameState(cpyGameState);
            destroySolutionContainer(solutionContainer);
            continue;
        }
        /* Generate successful */
        break;
    }
    if (attempt == 1000) {
        printf("Error: Generate failed to generate a board after 1,000 attempts.\n");
        return;
    }
    /* Fill cells with solution from ILP */
    for (row = 0; row < getSize(cpyGameState); row++) {
        for (col = 0; col < getSize(cpyGameState); col++) {
            for (value = 1; value <= getSize(cpyGameState); value++) {
                idx = getIndexOfVariable(solutionContainer, row, col, value);
                if (idx != -1 && solutionContainer->solution[idx] == 1.0) {
                    setCellValue(row,col,value,cpyGameState);
                }
            }
        }
    }
    /* Clear toClear cells. */
    while (cleared < toClear) {
        row = getRandom(0, getSize(gameState) - 1);
        col = getRandom(0, getSize(gameState) - 1);
        if (getCellValue(row, col, cpyGameState) == 0) {
            continue;
        } else {
            setCellValue(row, col, 0, cpyGameState);
            cleared++;
        }
    }
    /* Update History and Gamestate */
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) != getCellValue(row, col, cpyGameState)) {
                setCellValue(row, col, getCellValue(row, col, cpyGameState), gameState);
                if (historyChange == NULL) {
                    historyChange = createHistoryChange(row, col, 0, getCellValue(row, col, gameState));
                    tmpHistoryChange = historyChange;
                } else {
                    tmpHistoryChange->nextChange = createHistoryChange(row, col, 0, getCellValue(row, col, gameState));
                    tmpHistoryChange = tmpHistoryChange->nextChange;
                }
            }
        }
    }
    if (historyChange != NULL) {
        clearForwardHistory(*pHistoryState);
        historyState = createHistoryState();
        setChanges(historyState, historyChange);
        setPrevState(historyState, *pHistoryState);
        setNextState(*pHistoryState, historyState);
        *pHistoryState = historyState;
    }
    printBoard(gameState);
}

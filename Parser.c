#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"

/* Checks if user input matches given regular expressions */
bool matchesFormat(char *str, USER_CHOICE choice) {

    switch (choice) {
        case SET:
            if (strcmp(str, "set") == 0) {
                return true;
            }
            return false;
        case HINT:
            if (strcmp(str, "hint") == 0) {
                return true;
            }
            return false;
        case VALIDATE:
            if (strcmp(str, "validate") == 0) {
                return true;
            }
            return false;
        case RESET:
            if (strcmp(str, "reset") == 0) {
                return true;
            }
            return false;
        case EXIT:
            if (strcmp(str, "exit") == 0) {
                return true;
            }
            return false;
        case EDIT:
            if (strcmp(str, "edit") == 0) {
                return true;
            }
            return false;
        case PRINT_BOARD:
            if (strcmp(str, "print_board") == 0) {
                return true;
            }
            return false;
        case SOLVE:
            if (strcmp(str, "solve") == 0) {
                return true;
            }
            return false;
        case UNDO:
            if (strcmp(str, "undo") == 0) {
                return true;
            }
            return false;
        default:
            return false;
    }
}
/*TODO: Make more useful INVALIDs
 * Also, maybe add a "help" command? Weird they didn't ask. */

/* Scans user's input and returns it as String format */
USER_CHOICE parseCommand(GameState *gameState, char *input) {
    int k = 0, i = 0;
    char *str[MAX];
    char *endPtr;
    char *token = strtok(input, " \t\r\n");

    /* Reset contents of array */
    str[1] = NULL;

    while (token != 0) {
        str[k++] = token;
        token = strtok(0, " \t\r\n");
    }

    if (matchesFormat(str[0], SET)) {
        if (getGameMode(gameState) == INITMODE) {
            throw_illegalCommandForInit();
            printf("Details: <set X Y Z> may only be used in EDIT or SOLVE modes.\n");
            return INVALID_COMMAND;
        }
        if (k > 4) {
            throw_tooManyParametersError();
            printf("Details: <set X Y Z> accepts 3 parameters.\n");
            return INVALID_COMMAND;
        }
        if (k < 4) {
            throw_tooFewParametersError();
            printf("Details: <set X Y Z> accepts 3 parameters.\n");
            return INVALID_COMMAND;
        }
        for (i = 1; i <= 3; i++) {
            if (!isdigit(*str[i])) {
                throw_illegalParameterValueError();
                printf("Details: Parameter number %d is not a digit.\n", i);
                printf("<set X Y Z> - sets cell <X,Y> to value Z.\nX,Y,Z must be non-negative integers.\n");
                return INVALID_COMMAND;
            }
            if (*str[i] < 0 || *str[i] > getSize(gameState)) {
                throw_illegalParameterRangeError();
                printf("Details: Parameter number %d is not in the correct range.\n------------------------\n", i);
                printf("<set X Y Z> - sets cell <X,Y> to value Z.\nX,Y,Z must be within the board's range!\n");
                return INVALID_COMMAND;
            }
        }
        return SET;
    }

    if (matchesFormat(str[0], HINT) && k == 3 && isdigit(*str[1]) && isdigit(*str[2])) {
        hint(gameState,
             strtol(str[2], &endPtr, 10) - 1,
             strtol(str[1], &endPtr, 10) - 1);
        return HINT;
    }

    if (matchesFormat(str[0], VALIDATE)) {
        validate(gameState);

        return VALIDATE;
    }

    if (matchesFormat(str[0], UNDO)) {
        if (k > 0) {
            throw_tooManyParametersError();
            printf("Details: undo accepts NO parameters.\n");
            return INVALID_COMMAND;
        }
        if (getGameMode(gameState) == INITMODE) {
            throw_illegalCommandForInit();
            printf("Details: <undo> may only be used in EDIT or SOLVE modes.\n");
            return INVALID_COMMAND;
        }
        return UNDO;
    }

    if (matchesFormat(str[0], MARK_ERRORS)) {
        if (k > 1) {
            throw_tooManyParametersError();
            printf("Details: mark_errors accepts exactly ONE parameter - 1 or 0.\n");
            return INVALID_COMMAND;
        }
        if (k == 0) {
            throw_tooFewParametersError();
            printf("Details: mark_errors accepts exactly ONE parameter - 1 or 0.\n");
            return INVALID_COMMAND;
        }
        if (strcmp(str[1], "0") != 0 && strcmp(str[1], "1") != 0) {
            throw_illegalParameterRangeError();
            printf("Details: mark_errors accepts exactly ONE parameter - 1 or 0.\n");
        }
        return MARK_ERRORS;
    }

    if (matchesFormat(str[0], EXIT)) {
        printf("Exiting...\n");
        return EXIT;
    }

    if (matchesFormat(str[0], PRINT_BOARD)) {
        if (k > 0) {
            throw_tooManyParametersError();
            printf("Details: print_board accepts no additional parameters!\n");
            return INVALID_COMMAND;
        }
        return PRINT_BOARD;
    }

    if (matchesFormat(str[0], RESET)) {
        return RESET;
    }

    if (matchesFormat(str[0], EDIT)) {
        if (k > 1) {
            throw_tooManyParametersError();
            printf("Details: <edit [X]> may include at most ONE parameter of the file path.\n");
            return INVALID_COMMAND;
        }
        if (!validLoadPath(str[1])) {
            throw_loadPathError();
            return INVALID_COMMAND;
        }
        return EDIT;
    }

    if (matchesFormat(str[0], SOLVE)) {
        if (k > 1) {
            throw_tooManyParametersError();
            printf("Details: <solve X> must include exactly ONE parameter of the file path.\n");
            return INVALID_COMMAND;
        }
        if (k == 0) {
            throw_tooFewParametersError();
            printf("Details: <solve X> must include exactly ONE parameter of the file path.\n");
            return INVALID_COMMAND;
        }
        if (!validLoadPath(str[1])) {
            throw_loadPathError();
            return INVALID_COMMAND;
        }
        return SOLVE;
    }
    throw_unknownCommand();
    return INVALID_COMMAND;
}

/* Assumes parseCommand has determined input is correct.
 * Returns a new HistorayState according to the action that was made. */
HistoryState *executeCommand(GameState *gameState, USER_CHOICE commandType, char *input) {
    int k = 0, row, col, newValue, oldValue;
    char *str[MAX];
    char *endPtr;
    char *token = strtok(input, " \t\r\n");
    HistoryState *historyState = createHistoryState();
    HistoryChange *historyChange;
    SET_STATUS status;
    /* Reset contents of array */
    str[1] = NULL;

    while (token != 0) {
        str[k++] = token;
        token = strtok(0, " \t\r\n");
    }

    switch (commandType) {
        case (EDIT):
            if (k == 1) {
                gameState = loadFromFile(str[1]);
            } else {
                gameState = loadEmptyBoard();
            }
            setGameMode(gameState, EDITMODE);
            return historyState;

        case (SOLVE):
            gameState = loadFromFile(str[1]);
            setGameMode(gameState, SOLVEMODE);
            return historyState;

        case (SET):
            row = strtol(str[2], &endPtr, 10) - 1;
            col = strtol(str[1], &endPtr, 10) - 1;
            newValue = strtol(str[3], &endPtr, 10);
            oldValue = getCellValue(row, col, gameState, BOARD);
            status = set(gameState, row, col, newValue);
            if (status == CELL_FIXED) {
                printf("This cell is fixed, please try again.\n");
                return historyState;
            }
            if (getCellValue(row, col, gameState, BOARD) != newValue) {
                historyChange = createHistoryChange(row, col, oldValue, newValue);
                setChanges(historyState, historyChange);
            }
            return historyState;

        case (PRINT_BOARD):
            printBoard(gameState, BOARD);
            return historyState;

        case (MARK_ERRORS):
            strcmp(str[1], "0") == 0 ? setMarkErrors(gameState, false) : setMarkErrors(gameState, true);
            return historyState;
        default:
            return historyState;
    }
}

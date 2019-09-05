#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Parser.h"
#include "CommandExecutioner.h"

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
        case REDO:
            if(strcmp(str, "redo") == 0) {
                return true;
            }
            return false;
        case AUTOFILL:
            if (strcmp(str, "autofill") == 0) {
                return true;
            }
            return false;
        case MARK_ERRORS:
            if (strcmp(str, "mark_errors") == 0) {
                return true;
            }
            return false;
        case SAVE:
            if (strcmp(str, "save") == 0) {
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
    int k = 0;
    char *str[MAX];
    char inputCopy[MAX];
    char *token;

    /* Reset contents of array */
    str[1] = NULL;
    strcpy(inputCopy, input);
    token = strtok(inputCopy, " \t\r\n");

    while (token != 0) {
        str[k++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    k--;

    if (matchesFormat(str[0], SET)) {
        return validateSet(gameState, k, str);
    }

    if (matchesFormat(str[0], AUTOFILL)) {
        return validateAutofill(gameState, k);
    }

    if (matchesFormat(str[0], VALIDATE)) {
    }

    if (matchesFormat(str[0], UNDO)) {
        return validateUndo(gameState, k);
    }

    if (matchesFormat(str[0], REDO)) {
        return validateRedo(gameState, k);
    }

    if (matchesFormat(str[0], RESET)) {
        return validateReset(gameState, k);
    }

    if (matchesFormat(str[0], MARK_ERRORS)) {
       return validateMarkErrors(gameState, k, str);
    }

    if (matchesFormat(str[0], EXIT)) {
        return validateExit(k);
    }

    if (matchesFormat(str[0], PRINT_BOARD)) {
        return validatePrintBoard(gameState, k);
    }


    if (matchesFormat(str[0], EDIT)) {
        return validateEdit(k, str);
    }

    if (matchesFormat(str[0], SOLVE)) {
        return validateSolve(k, str);
    }

    if (matchesFormat(str[0], SAVE)) {
        return validateSave(gameState, k, str);
    }
    throw_unknownCommand();
    return INVALID_COMMAND;
}

/* Assumes parseCommand has determined input is correct. */
void executeCommand(GameState *gameState, HistoryState** historyState, USER_CHOICE commandType, char *input) {
    int k = 0, row, col, val;
    char *str[MAX];
    char inputCopy[MAX];
    char *endPtr;
    char *token;
    /* Reset contents of array */
    str[1] = NULL;
    strcpy(inputCopy, input);
    token = strtok(inputCopy, " \t\r\n");

    while (token != 0) {
        str[k++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    k--;

    switch (commandType) {
        case (EDIT):
            if (k == 1) {
                executeEdit(gameState, historyState, str[1], /* hasPath = */ true);
            } else {
                executeEdit(gameState, historyState, "", /* hasPath= */ false);
            }
            return;

        case (SOLVE):
            executeSolve(gameState, historyState, str[1]);
            return;

        case (SAVE):
            executeSave(gameState, str[1]);
            return;

        case (SET):
            col = strtol(str[1], &endPtr, 10) - 1;
            row = strtol(str[2], &endPtr, 10) - 1;
            val = strtol(str[3], &endPtr, 10);
            executeSet(gameState, historyState, row, col, val);
            return;

        case (UNDO):
            executeUndo(gameState, historyState);
            return;

        case (REDO):
            executeRedo(gameState, historyState);
            return;

        case (RESET):
            executeReset(gameState, historyState);
            return;

        case (AUTOFILL):
            executeAutofill(gameState, historyState);
            return;

        case (PRINT_BOARD):
            printBoard(gameState, BOARD);
            return;

        case (MARK_ERRORS):
            strcmp(str[1], "0") == 0 ? setMarkErrors(gameState, false) : setMarkErrors(gameState, true);
            return;

        case (EXIT):
            printf("Exiting...\n");
            destroyAllHistory(*historyState);
            free(historyState);
            destroyGameState(gameState);
            exit(EXIT_SUCCESS);
        default:
            return;
    }
}

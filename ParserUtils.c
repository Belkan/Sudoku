#include "ParserUtils.h"

bool isMode(GameState *gameState, GAME_MODE gameMode) {
    if (getGameMode(gameState) == gameMode) {
        throw_illegalCommandForMode(gameMode);
        return true;
    }
    return false;
}

bool paramsCountCorrect(int params, int minParams, int maxParams) {
    if (params > maxParams) {
        throw_tooManyParametersError();
        return false;
    }
    if (params < minParams) {
        throw_tooFewParametersError();
        return false;
    }
    return true;
}

bool paramsAreDigits(char **input, int params) {
    int i;
    for (i = 1; i <= params; i++) {
        if (!isdigit(*input[i])) {
            throw_illegalParameterValueError();
            printf("Details: Parameter number %d is not a digit.\n", i);
            return false;
        }
    }
    return true;
}

bool paramsInRange(char **input, int params, int minVal, int maxVal) {
    int i;
    char *endPtr;
    for (i = 1; i <= params; i++) {
        if (strtol(input[i], &endPtr, 10) < minVal || strtol(input[i], &endPtr, 10) > maxVal) {
            throw_illegalParameterRangeError();
            printf("Details: Parameter number %d is not in the correct range.\n", i);
            return false;
        }
    }
    return true;
}

USER_CHOICE validateSet(GameState *gameState, int params, char **input) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 3, 3)) {
        printf("Details: <set X Y Z> accepts exactly 3 parameters.\n");
        return INVALID_COMMAND;
    }
    if (!paramsAreDigits(input, params)) {
        return INVALID_COMMAND;
    }
    if (!paramsInRange(input, params, 1, getSize(gameState))) {
        printf("<set X Y Z> - sets cell <X,Y> to value Z.\nX,Y,Z must be within the board's range!\n");
        return INVALID_COMMAND;
    }
    return SET;
}


USER_CHOICE validateAutofill(GameState* gameState, int params) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: <autofill> accepts NO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        throw_illegalCommandForCurrentBoard();
        printf("Details: <autofill> cannot be used on an erroneous board.\n");
        return INVALID_COMMAND;
    }
    return AUTOFILL;
}

USER_CHOICE validateUndo(GameState* gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)){
        printf("Details: undo accepts NO parameters.\n");
        return INVALID_COMMAND;
    }
    return UNDO;
}

USER_CHOICE validateRedo(GameState* gameState, int params){
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)){
        printf("Details: redo accepts NO parameters.\n");
        return INVALID_COMMAND;
    }
    return REDO;
}

USER_CHOICE validateReset(GameState* gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    } if (!paramsCountCorrect(params, 0, 0)){
        printf("Details: reset accepts NO parameters.\n");
    }
    return RESET;
}

USER_CHOICE validateMarkErrors(GameState* gameState, int params, char **input) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 1, 1) || !paramsInRange(input, 1, 0, 1)) {
        printf("Details: mark_errors accepts exactly ONE parameter - 1 or 0.\n");
        return INVALID_COMMAND;
    }
    return MARK_ERRORS;
}

USER_CHOICE validateExit(int params) {
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: exit accepts NO parameters.\n");
        return INVALID_COMMAND;
    }
    return EXIT;
}

USER_CHOICE validatePrintBoard(GameState* gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: print_board accepts NO parameters.\n");
        return INVALID_COMMAND;
    }
    return PRINT_BOARD;
}

USER_CHOICE validateEdit(int params, char** input) {
    if (!paramsCountCorrect(params, 0, 1)) {
        printf("Details: <edit [X]> may include at most ONE parameter of the file path.\n");
        return INVALID_COMMAND;
    }
    if (params == 1 && !validLoadPath(input[1])) {
        return INVALID_COMMAND;
    }
    return EDIT;
}

USER_CHOICE validateSolve(int params, char** input) {
    if (!paramsCountCorrect(params, 1, 1)) {
        printf("Details: <solve X> must include exactly ONE parameter of the file path.\n");
        return INVALID_COMMAND;
    }
    if (!validLoadPath(input[1])) {
        throw_filePathError();
        return INVALID_COMMAND;
    }
    return SOLVE;
}

USER_CHOICE validateSave(GameState* gameState, int params, char** input) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 1, 1)) {
        printf("Details: <save X> must include exactly ONE parameter of the file path.\n");
        return INVALID_COMMAND;
    }
    /*if (!validLoadPath(input[1])) {
        throw_filePathError();
        return INVALID_COMMAND;
    }*/
    return SAVE;
}


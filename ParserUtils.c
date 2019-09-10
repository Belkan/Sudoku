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
            printf("Details: Parameter number %d is not in the correct range of %d to %d.\n", i, minVal, maxVal);
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
        printf("Details: <set X Y Z> expects exactly 3 parameters.\n");
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


USER_CHOICE validateAutofill(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: <autofill> expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        throw_illegalCommandForCurrentBoard();
        printf("Details: <autofill> cannot be used on an erroneous board.\n");
        return INVALID_COMMAND;
    }
    return AUTOFILL;
}

USER_CHOICE validateUndo(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: undo expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    return UNDO;
}

USER_CHOICE validateRedo(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: redo expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    return REDO;
}

USER_CHOICE validateReset(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: reset expects NO parameters.\n");
    }
    return RESET;
}

USER_CHOICE validateMarkErrors(GameState *gameState, int params, char **input) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 1, 1) || !paramsInRange(input, 1, 0, 1)) {
        printf("Details: mark_errors expects exactly ONE parameter - 1 or 0.\n");
        return INVALID_COMMAND;
    }
    return MARK_ERRORS;
}

USER_CHOICE validateExit(int params) {
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: exit expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    return EXIT;
}

USER_CHOICE validatePrintBoard(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: print_board expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    return PRINT_BOARD;
}

USER_CHOICE validateEdit(int params, char **input) {
    if (!paramsCountCorrect(params, 0, 1)) {
        printf("Details: <edit [X]> may include at most ONE parameter of the file path.\n");
        return INVALID_COMMAND;
    }
    if (params == 1 && !validLoadPath(input[1])) {
        throw_filePathError();
        return INVALID_COMMAND;
    }
    if (params == 1 && !validFileFormat(input[1])) {
        throw_invalidFileFormatError();
        return INVALID_COMMAND;
    }
    return EDIT;
}

USER_CHOICE validateSolve(int params, char **input) {
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

USER_CHOICE validateSave(GameState *gameState, int params, char **input) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 1, 1)) {
        printf("Details: <save X> must include exactly ONE parameter of the file path.\n");
        return INVALID_COMMAND;
    }
    if (!validLoadPath(input[1])) {
        throw_filePathError();
        return INVALID_COMMAND;
    }
    if (getGameMode(gameState) == EDITMODE) {
        if (!isBoardLegal(gameState)) {
            throw_illegalCommandForCurrentBoard();
            printf("Details: Board is erroneous in EDIT mode, please fix the board before saving.\n");
            return INVALID_COMMAND;
        }
        if (!isSolvable(gameState)) {
            throw_unsolvableFileErrror();
            return INVALID_COMMAND;
        }
    }
    return SAVE;
}

USER_CHOICE validateValidate(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: <validate> expects NO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        throw_illegalCommandForCurrentBoard();
        printf("Details: <validate> cannot be used on an erroneous board. Please fix the board and try again.\n");
        return INVALID_COMMAND;
    }
    return VALIDATE;
}

USER_CHOICE validateGuess(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 1, 1)) {
        printf("Details: <guess X> expects exactly ONE parameter.\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        throw_illegalCommandForCurrentBoard();
        printf("Details: <guess X> cannot be used on an erroneous board. Please fix the board and try again.\n");
        return INVALID_COMMAND;
    }
    return GUESS;
}

USER_CHOICE validateHint(GameState *gameState, int params, char **input) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 2, 2)) {
        printf("Details: <hint X Y> expects exactly TWO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!paramsAreDigits(input, params)) {
        return INVALID_COMMAND;
    }
    if (!paramsInRange(input, params, 1, getSize(gameState))) {
        printf("Details: <hint X Y> - X,Y must be within the board's range!\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        printf("Details: <hint X Y> cannot be used on an erroneous board. Please fix the board and try again.\n");
        return INVALID_COMMAND;
    }
    return HINT;
}

USER_CHOICE validateGuessHint(GameState *gameState, int params, char **input) {
    if (isMode(gameState, INITMODE) || isMode(gameState, EDITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 2, 2)) {
        printf("Details: <guess_hint X Y> expects exactly TWO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!paramsAreDigits(input, params)) {
        return INVALID_COMMAND;
    }
    if (!paramsInRange(input, params, 1, getSize(gameState))) {
        printf("Details: <guess_hint X Y> - X,Y must be within the board's range!\n");
        return INVALID_COMMAND;
    }
    if (!isBoardLegal(gameState)) {
        printf("Details: <guess_hint X Y> cannot be used on an erroneous board. Please fix the board and try again.\n");
        return INVALID_COMMAND;
    }
    return GUESS_HINT;
}

USER_CHOICE validateNumSolutions(GameState *gameState, int params) {
    if (isMode(gameState, INITMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 0, 0)) {
        printf("Details: <num_solutions> expects exactly ONE parameter.\n");
        return INVALID_COMMAND;
    }
    return NUM_SOLUTIONS;
}

USER_CHOICE validateGenerate(GameState *gameState, int params, char** input) {
    if (isMode(gameState, INITMODE) || isMode(gameState, SOLVEMODE)) {
        return INVALID_COMMAND;
    }
    if (!paramsCountCorrect(params, 2, 2)) {
        printf("Details: <generate X Y> expects exactly TWO parameters.\n");
        return INVALID_COMMAND;
    }
    if (!paramsAreDigits(input, params)) {
        return INVALID_COMMAND;
    }
    if (!paramsInRange(input, params, 1, getSize(gameState)*getSize(gameState))){
        return INVALID_COMMAND;
    }
    return GENERATE;
}

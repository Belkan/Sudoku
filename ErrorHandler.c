#include "ErrorHandler.h"

/* Errors regarding loading boards from given text file */

void throw_filePathError() {
    printf("Error: incorrect file path given! Please try again.\n");
}

void throw_unsolvableFileErrror() {
    printf("Error: unsolvable boards may not be saved! Please try again.\n");
}

void throw_invalidFileFormatError() {
    printf("Error: incorrect file format given! Please try again.\n");
}

/* Errors regarding parsing commands given as input */
void throw_illegalCommandNameError() {
    printf("Error: invalid command given! Please try again.\n");
}

void throw_illegalParameterRangeError() {
    printf("Error: parameters given are not in range for this command! Please try again.\n------------------------\n");
}

void throw_illegalParameterValueError() {
    printf("Error: parameters given have illegal values for current board state. Please try again.\n------------------------\n");
}

void throw_tooManyParametersError() {
    printf("Error: too many parameters for given command. Please try again.\n------------------------\n");
}

void throw_tooFewParametersError() {
    printf("Error: too few parameters for given command. Please try again.\n------------------------\n");
}

/* TODO: maybe add which commands are available in each mode */
void throw_illegalCommandForMode(GAME_MODE gameMode) {
    switch (gameMode) {
        case (INIT_MODE):
            printf("Error: command is illegal for INIT board mode. Only available commands in this mode are solve and edit. Please try again.\n------------------------\n");
            break;
        case (EDIT_MODE):
            printf("Error: command is illegal for EDIT board mode. Please try again.\n");
            break;
        case (SOLVE_MODE):
            printf("Error: command is illegal for EDIT board mode. Please try again.\n");
            break;
        default:
            break;
    }
}

void throw_illegalCommandForCurrentBoard() {
    printf("Error: this command is illegal for the current state of the board.\n");
}

void throw_unknownCommand() {
    printf("Error: this command doesn't exist. The available commands are:\n solve, edit, mark_errors,\n print_board, set,"
           " validate,\n guess, generate, undo,\n redo, save, hint,\n guess_hint, num_solutions, autofill,\n reset, exit.\n");
}

void throw_nothingToUndo() {
    printf("Error: there is no move to undo.\n");
}

void throw_nothingToRedo() {
    printf("Error: there is no move to redo.\n");
}

void throw_boardUnsolvable() {
    printf("Error: The board is unsolvable in its current state.\n");
}

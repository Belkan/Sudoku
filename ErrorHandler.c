#include "ErrorHandler.h"

/* Errors regarding loading boards from given text file */
void throw_rowSizeNotFoundError() {
    printf("Error: row size not found while loading file! Please specify another file!\n");
}

void throw_colSizeNotFoundError() {
    printf("Error: column size not found while loading file! Please specify another file!\n");
}

void throw_loadedInWrongModeError() {
    printf("Error: files cannot be loaded in INIT mode!\n");
}

void throw_loadPathError() {
    printf("Error: incorrect file path given!\n");
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

void throw_illegalCommandForInit() {
    printf("Error: command is illegal for INIT board mode. Only available commands are solve and edit. Please try again.\n------------------------\n");
}

void throw_illegalCommandForEdit() {
    printf("Error: command is illegal for EDIT board mode. Please try again.\n");
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


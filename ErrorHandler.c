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

void throw_illegalCommandForCurrentMode() {
    printf("Error: command is illegal for current board mode. Please try again.\n------------------------\n");
}

void throw_unknownCommand() {
    printf("Error: this command doesn't exist. The available commands are:\n solve, edit, mark_errors, print_board, set,"
           " validate, guess, generate, undo, redo, save, hint, guess_hint, num_solutions, autofill, reset, exit.\n");
}

#include "FileHandler.h"

/* Function to check for validity of loading a file: returns true if file can be loaded */
bool validLoadPath (char *filePath) {
    FILE *file;
    char *rowSize = (char *)malloc(CHAR_MAX), *colSize = (char *)malloc(CHAR_MAX);
    char *str[MAX];
    char *token;
    char *currLine = "First line of the file";
    int idx = 0;

    /* File exists and can be loaded */
    if ((file = fopen(filePath, "r")) != NULL) {
        /* Break line using delimeter */
        str[0] = NULL, str[1] = NULL;
        token = strtok(currLine, " \t\r\n");
        while (token != 0){
            str[idx++] = token;
            token = strtok(0, " \t\r\n");
        }

        /* Read row & col sizes */
        rowSize = str[0];
        colSize = str[1];

        if (!rowSize) {
            throw_rowSizeNotFoundError();
            /* Return old game */
            return false;
        }
        if (!colSize) {
            throw_colSizeNotFoundError();
            /* Return old game */
            return false;
        }
    }
    return false;
}

GameState *loadEmptyBoard() {
    GameState *gameState = createGameState(3, 3);
    return gameState;
}

/* Function to load up a saved game board and update our game state with it */
GameState *loadFromFile (char *filePath) {
    char *str[MAX];
    char *token;
    char *rowSize = (char *)malloc(CHAR_MAX), *colSize = (char *)malloc(CHAR_MAX);
    int i = 0, k = 0, j = 0, idx = 0;
    char *currLine = "Read this from file";
    FILE *loadedGame;
    GameState *newGame;

    /* Load up the game */
    loadedGame = fopen(filePath, "r");

    /* Read first line of loaded game into board */
    fgets(currLine, CHAR_MAX, loadedGame);

    /* Break line using delimeter */
    str[0] = NULL, str[1] = NULL;
    token = strtok(currLine, " \t\r\n");
    while (token != 0){
        str[idx++] = token;
        token = strtok(0, " \t\r\n");
    }

    /* Read row & col sizes */
    rowSize = str[0];
    colSize = str[1];

    /* Get rid of old board to load up new one */
    newGame = createGameState(atoi(rowSize), atoi(colSize));

    /* Read board */
    for (i = 0; i < atoi(rowSize); i++) {
        k = 0;
        /* Grab line to read */
        fgets(currLine, CHAR_MAX, loadedGame);

        /* Iterate over line's whitespaces */
        while (currLine[j] == ' ' || currLine[j] == '\t' || currLine[j] == '\r' || currLine[j] == '\n') {
            if (currLine[j] == '\n') {
                break;
            }
            j++;
        }

        /* Reached end of the line */
        if (currLine[j] == '\n') {
            continue;
        }

        /* Read digits to board */
        if (isdigit(currLine[j])) {
            setCellValue(i, k, currLine[j], newGame, BOARD);
        }
        k++;
        /* Read fixed cells to board */
        if (currLine[j] == '.') {
            setFixed(i, k, true, newGame);
        }
    }

    /* Close the game */
    fclose(loadedGame);

    /* Free resources */
    free(rowSize);
    free(colSize);

    return newGame;
}


/* Check if given path is valid for saving a file. */
bool validSavePath (char *filePath) {
    return false;
}

/* Function to save a board to a file at a given path. Paths can be relative or absolute. */
void saveToFile (char *filePath, GameState *currGame) {
    int rowsInBlock = getRowsInBlock(currGame);
    int colInBlock = getColsInBlock(currGame);
    int rowIdx = 0, colIdx = 0;
    int cell = 0;
    FILE *saveGame = fopen(filePath, "w");

    /* Write rows in block and cols in block to head of saved text file */
    fprintf(saveGame, "%d %d\n", rowsInBlock, colInBlock);

    /* Iterate current game state to load unto file */
    for (rowIdx = 0; rowIdx < getSize(currGame); rowIdx++) {
        for (colIdx = 0; colIdx < getSize(currGame); colIdx++) {
            /* Get current cell */
            cell = getCellValue(rowIdx, colIdx, currGame, BOARD);
            fprintf(saveGame, "%d", cell);

            /* Check if saving dot for fixed cell is required */
            if (isFixed(rowIdx, colIdx, currGame)) {
                fprintf(saveGame, ". ");
            }
            else {
                fprintf(saveGame, " ");
            }

            /* Reached end of the line */
            if (colIdx == getSize(currGame) - 1) {
                fprintf(saveGame, "\n");
            }
        }
    }

    /* Close the saved game */
    fclose(saveGame);

}

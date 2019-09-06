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
            free(rowSize);
            free(colSize);
            return false;
        }
        if (!colSize) {
            throw_colSizeNotFoundError();
            free(rowSize);
            free(colSize);
            return false;
        }
    }
    else {
        throw_filePathError();
        return false;
    }
    free(rowSize);
    free(colSize);
    return true;
}

GameState *loadEmptyBoard() {
    GameState *gameState = createGameState(3, 3);
    return gameState;
}

/* Utility function for loader: finds next position in line to read cell from. */
int getNextIdx(char *currLine, int currIdx) {
    int i = currIdx + 1;

    if (isdigit(currLine[currIdx]) || currLine[currIdx] == '.') {
        return currIdx;
    }

    /* Find next digit or fixed cell markup or \n in the line. */
    while (currLine[i] == ' ' || currLine[i] == '\t' || currLine[i] == '\r') {
        i++;
    }
    return i;
}

/* Function to load up a saved game board and update our game state with it */
GameState *loadFromFile (char *filePath) {
    char *rowSize = (char *)malloc(CHAR_MAX), *colSize = (char *)malloc(CHAR_MAX);
    int idx = 0, rows = 0, cols = 0, rowIdx = 0, colIdx = 0, cell = 0, lineIdx = 0;
    char *currLine = (char *)malloc(CHAR_MAX);
    FILE *loadedGame;
    GameState *newGame;

    /* Load up the game */
    loadedGame = fopen(filePath, "r");

    /* Read first line of loaded game into board */
    fgets(currLine, CHAR_MAX, loadedGame);

    /* Read col/row values from text file. */
    rows = currLine[getNextIdx(currLine, idx++)] - '0';
    cols = currLine[getNextIdx(currLine, idx)] - '0';

    /* Get rid of old board to load up new one */
    newGame = createGameState(rows, cols);

    /* Read board */
    while (fgets(currLine, CHAR_MAX, loadedGame)) {
        lineIdx = 0;
        /* Iterate line retrieved to update board. */
        for (idx = 0; idx < rows * cols; idx++) {
            lineIdx = getNextIdx(currLine, lineIdx);
            cell = currLine[lineIdx++];

            /* Check if cell needs to be fixed. */
            if ((cell - '0') == -2) {
                setFixed(getPrevRow(rowIdx, colIdx), getPrevCol(rows * cols, colIdx), true, newGame);
                idx--;
            }
            else {
                setCellValue(rowIdx, colIdx, cell - '0', newGame, BOARD);
                /* Handle edge case of fixing last column. */
                if (colIdx == rows * cols - 1) {
                    if (currLine[getNextIdx(currLine, lineIdx)] - '0' == -2) {
                        setFixed(rowIdx, colIdx, true, newGame);
                    }
                }
                /* Update row/col indexes. */
                rowIdx = getNextRow(rows * cols, rowIdx, colIdx);
                colIdx = getNextCol(rows * cols, colIdx);
            }
        }
    }

    /* Close the game */
    fclose(loadedGame);

    /* Free resources */
    free(rowSize);
    free(colSize);

    return newGame;
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

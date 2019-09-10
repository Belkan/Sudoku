#include "FileHandler.h"

/* Utility function for valid load path. */
int getNumberEndPos(char *currLine, int start) {
    while (isdigit(currLine[++start]));
    return start;
}

/* Function to check for validity of loading a file: returns true if file can be loaded */
bool validLoadPath (char *filePath) {
    FILE *file;
    /* File exists and can be loaded */
    if ((file = fopen(filePath, "r")) == NULL) {
        return false;
    }
    return true;
}

/* Function to check whether loaded file has valid format. */
bool validFileFormat (char *filePath) {
    FILE *file = fopen(filePath, "r");
    char *currLine = (char *) malloc(CHAR_MAX);
    int counter = 0, idx = 0, rowsInlbock = -1, colsInBlock = -1, size = 0, cell = 0, rowsAmount = 0;

    /* Make sure first line has correct format. */
    fgets(currLine, sizeof(currLine), file);
    for (idx = 0; idx < size_t2int(sizeof(currLine)); idx++) {
        if (currLine[idx] == '\n') {
            break;
        }
        if ((isdigit(currLine[idx]) && isblank(currLine[idx + 1])) ||
            (isdigit(currLine[idx]) && isspace(currLine[idx + 1]))) {
            /* Determine if we have found rowsInBlock element of size or cols in block. */
            if (rowsInlbock < 0) {
                rowsInlbock = currLine[idx] - '0';
            }
            else {
                colsInBlock = currLine[idx] - '0';
            }
            counter++;
        }
        if (!isdigit(currLine[idx]) && !isspace(currLine[idx]) && !isblank(currLine[idx])) {
            return false;
        }
    }
    /* More than 2 numbers in header files, negative rows in block value or negative cols in block value:
     * these are all sufficient conditions for invalid file format. */
    if (counter != 2 || rowsInlbock < 0 || colsInBlock < 0) return false;

    size = rowsInlbock * colsInBlock;
    /* Check all other lines don't contain illegal characters, or cells out of range. */
    while (fgets(currLine, CHAR_MAX, file)) {
        rowsAmount++;
        counter = 0;
        idx = 0;
        while (currLine[idx] != '\n') {
            if (isdigit(currLine[idx])) {
                cell = nextInt(idx, currLine);
                counter++;;
                /* Make sure all entries of loaded board aren't too big. */
                if (!cellInRange(cell, size)) return false;
                while (isdigit(currLine[idx + 1])) idx++;
            }

            /* Check if we have found an illegal character.
             * Legal characters are integers within range for board, or blanks.*/
            if (!isdigit(currLine[idx]) && !isblank(currLine[idx])
                  && currLine[idx] != '.' && !isspace(currLine[idx])) {
                return false;
            }
            idx++;
        }
        /* A line cannot be too short or too long, e.g. if size is 9 we can't have a line with 4 integers. */
        if (counter != size) return false;
    }
    /* We can't have too few lines in file. */
    if (rowsAmount != size) return false;

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
            cell = currLine[lineIdx];
            if (isdigit(cell)) {
                cell = nextInt(lineIdx, currLine);
                while (isdigit(currLine[lineIdx])) lineIdx++;
            } else {
                lineIdx++;
            }

            /* Check if cell needs to be fixed. */
            if ((cell - '0') == -2) {
                setFixed(getPrevRow(rowIdx, colIdx), getPrevCol(rows * cols, colIdx), true, newGame);
                idx--;
            }
            else {
                setCellValue(rowIdx, colIdx, cell, newGame);
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
            cell = getCellValue(rowIdx, colIdx, currGame);

            /* Reached end of the line */
            if (colIdx == getSize(currGame - 1)) {
                fprintf(saveGame, "%d\n", cell);
            }
            else {
                /* Save cell to file. In EDITMODE, all cells are marked as fixed upon saving. */
                if (getGameMode(currGame) == EDITMODE) {
                    if (cell != 0) {
                        fprintf(saveGame, "%d. ", cell);
                    }
                    else {
                        fprintf(saveGame, "%d ", cell);
                    }
                }
                /* Save cell to file. In SOLVEMODE, only fixed cells are marked as fixed upon saving. */
                if (getGameMode(currGame) == SOLVEMODE) {
                    if (isFixed(rowIdx, colIdx, currGame)) {
                        fprintf(saveGame, "%d. ", cell);
                    }
                    else {
                        fprintf(saveGame, "%d ", cell);
                    }
                }
            }
        }
    }

    /* Close the saved game */
    fclose(saveGame);
}

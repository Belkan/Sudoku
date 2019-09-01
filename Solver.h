#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "Game.h"

typedef enum solution_type {
    DETERMINISTIC,
    RANDOM
} SOLUTION_TYPE ;

typedef struct recursion_stack {
    int capacity;
    int top;
    int *rows;
    int *cols;
    int *vals;
} RECURSION_STACK ;

/* TODO test this */
/* Use exhaustive backtracking algorithm (using stack) to count the number of solutions for the board. */
int solutionCounter(GameState *gameState);

/* Create stack that replaces recursion while getting #solutions for board. */
struct recursion_stack* createStack(int capacity);

/* Destroy aforementioned stack. */
void destroyStack(struct recursion_stack *stack);

/* Check if stack is full (i.e. stack overflow). */
bool isFull(struct recursion_stack *stack);

/* Check if stack is empty. */
bool isEmpty(struct recursion_stack *stack);

/* Push new game state to top of the stack. */
bool push(struct recursion_stack *stack, int row, int col, int val);

/* Removes top element of stack and returns true on success, false otherwise. */
bool pop(struct recursion_stack *stack);

/* Retrieves top element of the stack. */
int peek(struct recursion_stack *stack);

/* Checks if there is a solution to the board. Assumes solution is empty. */
bool isSolvableRecursion(GameState *gameState, int row, int col, SOLUTION_TYPE type);
/* Subfunctions for isSolvableRecursion */
int getNextRow(int size, int row, int col);
int getNextCol(int size, int col);
void swap(int *x, int *y);

/* Checks if current state is solvable using deterministic algorithm. If solvable, updates solution.*/
bool isSolvable(GameState *gameState);

/* Generates the initial random solution. Assumes solution is empty.*/
void generateRandomSolution(GameState *gameState);



#endif


#ifndef SUDOKU_SOLVERUTILS_H
#define SUDOKU_SOLVERUTILS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* Stack to emulate recursion for exhaustive backtracking algorithm. */
typedef struct recursion_stack {
    int capacity;
    int top;
    int *rows;
    int *cols;
} RECURSION_STACK ;

/* Create stack that replaces recursion while getting #solutions for board. */
struct recursion_stack* createStack(int capacity);

/* Destroy aforementioned stack. */
void destroyStack(struct recursion_stack *stack);

/* Check if stack is full (i.e. stack overflow). */
bool isFull(struct recursion_stack *stack);

/* Check if stack is empty. */
bool isEmpty(struct recursion_stack *stack);

/* Push new game state to top of the stack. */
bool push(struct recursion_stack *stack, int row, int col);

/* Removes top element of stack and returns true on success, false otherwise. */
bool pop(struct recursion_stack *stack);

/* Retrieves top row element of the stack. */
int peekRow(struct recursion_stack *stack);

/* Retrieves top column element of the stack. */
int peekCol(struct recursion_stack *stack);

/* Various "general purpose" utility functions. */
int getNextRow(int size, int row, int col);
int getNextCol(int size, int col);
int getPrevRow(int row, int col);
int getPrevCol(int size, int col);
void swap(int *x, int *y);

#endif
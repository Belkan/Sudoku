#include "SolverUtils.h"

/* Initialize stack of given capacity. */
struct recursion_stack* createStack(int capacity) {
    struct recursion_stack *stack = malloc(sizeof(struct recursion_stack));
    int idx = 0;

    /* Initially, top index is 0. Index of -1 denotes empty stack. */
    stack->top = 0;
    stack->capacity = capacity;
    /* Start with cell [1,1] and set it to value 1, the least value. */
    stack->rows = (int *) malloc(capacity * sizeof(int));
    stack->rows[0] = 0;
    stack->cols = (int *) malloc(capacity * sizeof(int));
    stack->cols[0] = 0;

    /* Set other entries to 0. */
    for (idx = 1; idx < capacity; idx++) {
        stack->rows[idx] = 0;
        stack->cols[idx] = 0;
    }
    return stack;
}

void destroyStack(struct recursion_stack *stack) {
    free(stack->rows);
    free(stack->cols);
    free(stack);
}

/* Check if stack is full (i.e. stack overflow). */
bool isFull(struct recursion_stack *stack) {
    if (stack->top == stack->capacity) return true;
    return false;
}

/* Check if stack is empty. */
bool isEmpty(struct recursion_stack *stack) {
    if (stack->top == -1) return true;
    return false;
}

/* Push new game state to top of the stack. */
bool push(struct recursion_stack *stack, int row, int col) {
    /* Avoid stack overflow. */
    if (isFull(stack)) {
        return false;
    }
    ++stack->top;
    stack->rows[stack->top] = row;
    stack->cols[stack->top] = col;
    return true;
}

/* Removes top element of stack. */
bool pop(struct recursion_stack *stack) {
    /* Avoid stack underflow. */
    if (isEmpty(stack)) {
        return false;
    }
    --stack->top;
    return true;
}


/* Retrieves top row element of the stack. */
int peekRow(struct recursion_stack *stack) {
    return stack->rows[stack->top];
}

/* Retrieves top column element of the stack. */
int peekCol(struct recursion_stack *stack) {
    return stack->cols[stack->top];
}

/* General purpose utility functions below. */
int getNextRow(int size, int row, int col) {
    if (col < size - 1) {
        return row;
    } else {
        return row + 1;
    }
}

int getNextCol(int size, int col) {
    if (col < size - 1) {
        return col + 1;
    } else {
        return 0;
    }
}

int getPrevRow(int row, int col) {
    if (col == 0) {
        return row - 1;
    }
    return row;
}

int getPrevCol(int size, int col) {
    if (col == 0) {
        return size - 1;
    }
    return col - 1;
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


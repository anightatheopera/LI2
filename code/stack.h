#ifndef STACK_H 
#define STACK_H

#include "types.h"

typedef struct stack {
    void **values;
    int allocsize;
    int size;
} Stack;

Stack *stackinit(int);
void *pop(Stack *);
void push(Stack *, void *);
void *top(Stack *);
void print_stack(Stack *);

#endif
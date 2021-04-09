#ifndef STACK_H 
#define STACK_H

#include "types.h"

typedef struct stack {
    Types **values;
    int allocsize;
    int size;
} Stack;

Stack *stackinit(int);
Types *pop(Stack*);
void push(Stack*, Types*);
Types *top(Stack *);
void print_stack(Stack *);

#endif
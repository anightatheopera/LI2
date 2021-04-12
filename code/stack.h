#ifndef STACK_H 
#define STACK_H
#include "types.h"

/**
 * Estrutura da stack
 */
typedef struct stack {
    /*@{*/
    void **values; /**< os valores que estão na stack*/
    int allocsize; /**< o espaço alocado */
    int size; /**< o espaço ocupado */
    /*@{*/
} Stack;

Stack *stackinit(int);
void *pop(Stack *);
void push(Stack *, void *);
void *top(Stack *);
void print_stack(Stack *);

#endif
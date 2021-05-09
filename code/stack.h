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
    void **var; /**< as variáveis da stack */
    /*@{*/
} Stack;

Stack *stackinit(long);
void *pop(Stack *);
void push(Stack *, void *);
void print_stack(Stack *);

#endif
#ifndef TYPES_H 
#define TYPES_H
#include "stack.h"

/**
 * The enumeration of space dimension
 */
typedef enum { block  = 6, /** < Blocos */
               array  = 5, /** < Arrays */
               string = 4, /**< Strings */
               single = 3, /**< Caracteres */
               floats = 2, /**< Floats */
               number = 1 /**< Números inteiros */
} Diftypes;

/**
 * Estrura que contém os diferentes tipos de elemntos da stack
 */
typedef struct types {
    /*@{*/
    Diftypes type; /**< Enumeração dos diferentes tipos */
    struct stack *array; /** < Arrays */
    char *block; /**< Blocos */
    char *string; /**< Strings */
    long number; /**< Números inteiros */
    double floats; /**< Floats */
    char single; /**< Caracteres */
    /*@{*/
} Types;

Types *init(Diftypes);
Types *initNumber(int);
Types *initChar(char);
Types *initString(char*);
Types *initFloat(double);
Types *initBlock(char*);
Types *initArray(struct stack*);

#endif
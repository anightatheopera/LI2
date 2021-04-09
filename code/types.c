/**
 * @file Ficheiro que contém as funções que inicializam os diferentes tipos que a stack contém
 */
#include "types.h"
#include "stack.h"
#include <stdlib.h>

#define types(x) _Generic((x), \
    char: 0,                   \
    char *: 1,                 \
    int: 2,                    \
    double: 3                  )

/**
 * Esta função inicializa a stack
 * @param enum A enumeração dos diferentes tipos
 *
 * @returns O tipo a ser entregue
 */
Types* init(enum diftype d){
    Types* s = calloc(1, sizeof(Types));
    s->type = d;
    return s;
}

/**
 * Esta função inicializa os números inteiros da stack
 * @param int Um número inteiro
 *
 * @returns O tipo a ser entregue
 */
Types *initNumber(int n){
    Types *s = init(number);
    s->number= n;
    return s;
}

/**
 * Esta função inicializa os caracteres da stack
 * @param char Um caracter
 *
 * @returns O tipo a ser entregue
 */
Types *initChar(char n){
    Types *s = init(single);
    s->single= n;
    return s;
}

/**
 * Esta função inicializa as strings da stack
 * @param char* Uma string
 *
 * @returns O tipo a ser entregue
 */
Types *initString(char* n){
    Types *s = init(string);
    s->string = n;
    return s;
}

/**
 * Esta função inicializa os números decimais da stack
 * @param float Um número decimal
 *
 * @returns O tipo a ser entregue
 */
Types *initFloat(double n){
    Types *s = init(floats);
    s->floats = n;
    return s;
}
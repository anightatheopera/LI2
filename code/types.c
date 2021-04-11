/**
 * @file Ficheiro que contém as funções que inicializam os diferentes tipos que a stack contém
 */
#include "types.h"
#include "stack.h"
#include <stdlib.h>

/**
 * Esta função inicializa a stack
 * @param enum A enumeração dos diferentes tipos
 *
 * @returns O tipo a ser entregue
 */
Types *init(Diftypes d){
    Types *elem = calloc (1, sizeof(Types));
    elem->type = d;
    return elem;
}

/**
 * Esta função inicializa os números inteiros da stack
 * @param int Um número inteiro
 *
 * @returns O tipo a ser entregue
 */
Types *initNumber(int n){
    Types *elem = init(number);
    elem->number= n;
    return elem;
}

/**
 * Esta função inicializa os caracteres da stack
 * @param char Um caracter
 *
 * @returns O tipo a ser entregue
 */
Types *initChar(char n){
    Types *elem = init(single);
    elem->single= n;
    return elem;
}

/**
 * Esta função inicializa as strings da stack
 * @param char* Uma string
 *
 * @returns O tipo a ser entregue
 */
Types *initString(char* n){
    Types *elem = init(string);
    elem->string = n;
    return elem;
}

/**
 * Esta função inicializa os números decimais da stack
 * @param float Um número decimal
 *
 * @returns O tipo a ser entregue
 */
Types *initFloat(double n){
    Types *elem = init(floats);
    elem->floats = n;
    return elem;
}
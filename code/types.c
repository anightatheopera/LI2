/**
 * @file types.c
 * @brief Ficheiro que contém as funções que inicializam os diferentes tipos que a stack contém
 */
#include "types.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * Esta função inicializa a stack
 * @param d A enumeração dos diferentes tipos
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
 * @param n Um número inteiro
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
 * @param n Um caracter
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
 * @param n Uma string
 *
 * @returns O tipo a ser entregue
 */
Types *initString(char *n){
    Types *elem = init(string);
    elem->string = n;
    return elem;
}

/**
 * Esta função inicializa os números decimais da stack
 * @param n Um número decimal
 *
 * @returns O tipo a ser entregue
 */
Types *initFloat(double n){
    Types *elem = init(floats);
    elem->floats = n;
    return elem;
}

/**
 * Esta função inicializa os blocos da stack
 * @param n Um bloco
 *
 * @returns O tipo a ser entregue
 */
Types *initBlock(char *n){
    Types *elem = init(block);
    elem->block = n;
    return elem;
}
/**
 * @file Ficheiro que contém as funções principais da stack
 */

#include "stack2.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Inicializa uma stack
 * @param capacity A capacidade da stack
 * @returns Uma stack inicializada
 */
Stack* stackinit(int capacity){
    Stack* s = calloc(1, sizeof(Stack));
    s->allocsize = capacity;
    s->size = 0;
    s->values = calloc(capacity, sizeof(void*));
    return s;
}

/**
 * Retira o último elemento da stack
 * @param s A stack a alterar
 * 
 */
void* pop(Stack* s){
    if (s->size <= 0) return NULL;
    else {
      s->size--; 
      return s->values[s->size];
    }
}

/**
 * Adiciona o elemento à stack
 * @param s A stack a alterar
 * @param n Elemento a adicionar
 *
 */
void push(Stack* s, void* n){
    if(s->allocsize == s->size){
        s->allocsize *= 2;
        s->values = reallocarray(s->values,s->allocsize,sizeof(void*)); 
    } 
    s->values[s->size++]= n;
}


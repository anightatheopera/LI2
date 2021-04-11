/**
 * @file stack.c
 * @brief Ficheiro que contém as funções principais de manipulação da stack
 */

#include "stack.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Inicializa uma stack
 * @param capacity A capacidade da stack
 * @returns Uma stack inicializada
 */
Stack *stackinit(int capacity){
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    s->allocsize = capacity;
    s->size = 0;
    s->values = (void *) calloc(capacity, sizeof(void *));
    return s;
}

/**
 * Retira o último elemento da stack
 * @param s A stack a alterar
 * 
 */

void *pop(Stack* s){
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
void push(Stack *s, void *n){
    if(s->allocsize == s->size){
        s->allocsize *= 2;
        s->values = (void *) realloc(s->values, (s->allocsize + 1) * sizeof(void *)); 
    } 
    s->values[s->size++]= n;
}

/**
 * @brief Imprime a stack
 * 
 * @param s A stack a imprimir
 */
void print_stack(Stack *s) {
  for(int K = 0; K < s->size; K++) {
    Types *elem = s->values[K];
    Diftypes type = elem->type;
    switch(type) {
      case number:
        printf("%ld", elem->number); break;
      case floats:
        printf("%g", elem->floats); break;
      case single:
        printf("%c", elem->single); break;
      case string:
        printf("%s", elem->string); break;
    }
  }
  printf("\n");
}

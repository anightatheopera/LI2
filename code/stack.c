/**
 * @file Ficheiro que contém as funções principais da stack
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
    Stack *s = calloc(1, sizeof(Stack));
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
Types *pop(Stack* s){
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
void push(Stack *s, Types *n){
    if(s->allocsize == s->size){
        s->allocsize *= 2;
        s->values = realloc(s->values, s->allocsize* sizeof(Types *)); 
    } 
    s->values[s->size++]= n;
}

Types *top(Stack *s) {
  return s->values[s->size-1];
}

void print_stack(Stack *s) {
  for(int k = 0; k < s->size; k++) {
    Types *elem = s->values[k];
    switch(elem->type) {
      case number:
        printf(" %ld", elem->number); break;
      case floats:
        printf(" %g", elem->floats); break;
      case single:
        printf(" %c", elem->single); break;
      case string:
        printf(" %s", elem->string); break;
    }
  }
	printf("\n"); 
}
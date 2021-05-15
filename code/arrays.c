/**
 * @file arrays.c
 * @brief Este ficheiro contem as funções em arrays
 * 
 */
#include "arrays.h"
#include <stdlib.h>

/**
 * Concatenação de arrays
 * 
 * @param s A stack
 * @param y Array a concatenar com x
 * @param x Array a concatenar com y
 */
void cat_array (Stack *s, Types *y, Types *x){
    Stack *array = stackinit(x->array->size + y->array->size);
    array->var = s->var;
    for (int i=0; i < x->array->size; i++) push(array, x->array->values[i]);
    for (int i=0; i < y->array->size; i++) push(array, y->array->values[i]);
    push(s, initArray(array));
}

/**
 * Adiciona um elemento ao array
 * 
 * @param s A stack
 * @param y Elemento/Array
 * @param x Elemento/Array
 */
void add_array (Stack *s, Types *y, Types *x){
    if (x->type == array) { 
        push (x->array, y);
        push(s, x);
    } else {
        Stack *array = stackinit(100);
        array->var = s->var;      
        push (array, x); 
        for (int i=0; i<y->array->size; ++i) push(array, y->array->values[i]);
        push(s, initArray(array));
    } 
}

/**
 * Cria um certo número de réplicas de um array
 * 
 * @param s A stack
 * @param y Número de réplicas
 * @param x Array a replicar
 */
void replicate_array (Stack *s, int y, Types *x) {
    Stack *array = stackinit(x->array->size);
    array->var = s->var;
    while (y > 0 ) {	
        for (int i=0; i < x->array->size; i++) push(array, x->array->values[i]);
        y --;
    }
    push(s, initArray(array));
}

/**
 * Remove o primeiro elemento de um array e adiciona o à stack
 * 
 * @param s A stack
 * @param y Array a remover o primeiro elemento
 */
void first_array (Stack *s, Types *y) {
    Stack *array = stackinit(y->array->size);
    array->var = s->var;
    Types *x = y->array->values[0];
    for (int i=1; i< y->array->size; i++) {
        push(array, y->array->values[i]);
    }
    push(s, initArray(array));
    push(s, x);
}

/**
 * Remove o último elemento de um array e adiciona o à stack
 * 
 * @param s A stack
 * @param y Array a remover o último elemento
 */
void last_array (Stack *s, Types *y) {
    Types *x = pop(y->array);
	push(s, y);
    push(s, x);
}

/**
 * Coloca todos os elementos de um array na stack
 * 
 * @param s A stack
 * @param y O array
 */
void include_stack (Stack *s, Types *y) {
    for (int i=0; i < y->array->size; i++) push(s, y->array->values[i]);
}

/**
 * Coloca na stack um elemento de um array por indice
 * 
 * @param s A stack
 * @param y Indice
 * @param x Array
 */
void index_array(Stack *s, Types *y, Types *x) {
    push(s, x->array->values[y->number]);
}

/**
 * Coloca na stack um array com os primeiros y elementos do array inicial no topo da stack
 * 
 * @param s A stack
 * @param y Número de elementos
 * @param x Array inicial
 */
void init_array(Stack *s, Types *y, Types *x)  {
    int i=0;
    Stack *array = stackinit(100);
    array->var = s->var;
    for (i=0; i<y->number; i++) push(array, x->array->values[i]);
    push(s, initArray(array));
}

/**
 * Coloca na stack um array com os últimos y elementos do array inicial no topo da stack
 * 
 * @param s A stack
 * @param y Número de elementos
 * @param x Array inicial
 */
void tail_array(Stack *s, Types *y, Types *x)  {
    Stack *array = stackinit(100);
    array->var = s->var;
    for (; y->number>0; y->number--) push(array, x->array->values[(x->array->size)-(y->number)]);
    push(s, initArray(array));
}

/**
 * Coloca na stack um array com elementos na range de 0..y-1
 * 
 * @param s A stack
 * @param y Número de elementos da range
 */
void range_array (Stack *s, Types *y) {
    Stack *array = stackinit(y->number);
    array->var = s->var;
    for (int n = 0; n < y->number; n++) push(array, initNumber(n));
    push(s, initArray(array));
}

/**
 * Create a array object
 * 
 * @param s A stack
 * @param n Array a copiar
 */
Types *create_array (Stack *s, Stack *n) {
    Stack *array = stackinit(100);
    array->var = s->var;
    for (int i=0; i<n->size ; i++) {
        Types *y = n->values[i];
        push(array, y);
    }
    return initArray(array);
}
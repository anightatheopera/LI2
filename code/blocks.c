/**
 * @file blocks.c
 * @brief Este ficheiro contem as funções de implementação de blocos
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "parser.h"
#include "convertions.h"

/**
 * Executa um bloco a um caracter/numero
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void exec_block (Stack *s, char *block) {
    block++;
    block[strlen(block)-1] = '\0';

    parse(block, s);
    pop(s);
}

/**
 * Executa um bloco a uma string
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param n String onde será implementado o bloco
 */
void string_block (Stack *s, char *block, char *n) {
    char *new = calloc (1024, sizeof(char));
    Stack  *s2 = stackinit(100);
    
    block++;
    block[strlen(block)-1] = '\0';

    for (int i = 0; i<(int)strlen(n); i++) {
        push(s2, initChar(n[i]));
        parse(block, s2);
        pop(s2);
    }
    for (int k = 0; k < s2->size; k++) {
        Types *y = s2->values[k];
        conv_string(y);
        strcat(new, y->string);
    }
    free(s2);
    push(s, initString(new));
}

/**
 * Executa um bloco a um array
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param n Array onde será implementado o bloco
 */
void array_block (Stack *s, char *block, Stack *n) {
    Stack *array = stackinit(100);
    block++;
    block[strlen(block)-1] = '\0';
    
    for (int i = 0; i<(n->size); i++) {
        Stack *s2 = stackinit(100);
        push(s2, n->values[i]);
        parse(block, s2);
        for (int k = 0; k < s2->size-1; k++) {
            Types *y = s2->values[k];
            push(array, y);
        }
        free(s2);
    }

    free(n);
    push(s, initArray(array));
}

/**
 * Executa um bloco a um array/string
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param x Array/String onde será implementado o bloco
 */
void map_block (Stack *s, char *block, Types *x) {
    if (x->string) string_block(s, block, x->string);
    else array_block(s, block, x->array);
}

/**
 * Operação filter com bloco para string
 * 
 * @param s A stack
 * @param block Bloco a executar como filter
 * @param n String a implementar
 */
void filter_string (Stack *s, char *block, char *n) {
    string_block(s, block, n);
    Types *w = pop(s);
    char *new = calloc (strlen(w->string), sizeof(char));
    for (int i = 0, k=0; i<(int)strlen(w->string); i++)
        if (w->string[i] != '0') { new[k] = n[i]; k++; }

    free(w);
    push(s, initString(new));
}

/**
 * Operação filter com bloco para array
 * 
 * @param s A stack
 * @param block Bloco a executar como filter
 * @param n Array a implementar
 */
void filter_array (Stack *s, char *block, Stack *n) {
    array_block(s, block, n);
    Stack *w = pop(s);
    Stack *array = stackinit(100);
    for (int i = 0; i<w->size; i++)
        if (w->values[i] == 0) push(array, w->values[i]);
    push(s, initArray(array));
    free(w);
}

/**
 * Operação filter com bloco para strings e arrays
 * 
 * @param s A stack
 * @param block Bloco a executar como filter
 */
void filter_block (Stack* s, char *block) {
    Types *y = pop(s);
    if (y->string) filter_string(s, block, y->string);
    else filter_array(s, block, y->array);
}

/**
 * Operação fold de um bloco sobre um array
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param n Array a implementar o bloco
 */
void fold_array (Stack *s, char *block, Stack *n) {
    block++;
    block[strlen(block)-1] = '\0';

    while (n->size != 1) {
        parse(block, n);
        pop(n);
    }

    push(s, initArray(n));
}


void sort_block (Stack *s, char *block) {
    Stack *s2 = stackinit(100);
    block++;
    block[strlen(block)-1] = '\0';
    
    for (int i = 0; s->size != 0; i++) {
        Types *y = pop(s);
        push(s2, y);
        parse(block, s2);
        pop(s2);
    }
    while (s2->size != 0){
        Types *x = pop(s2);
        push(s, x);
    }
    int count = s->size;
    Types *temp;
    for (int j = 0; j < count; j++) {
      for (int k = j + 1; k < count; k++) {
          if(big_op(s->values[k], s->values[j]) == 1) {
              temp = s->values[j];
              s->values[j] = s->values[k];
              s->values[k] = temp;
          }
      }
    }
}

/**
 * Aplicação de um bloco enquanto deixar um truthy no topo da stack
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void w_block (Stack *s, char *block) {
    block++;
    block[strlen(block)-1] = '\0';
    int flag = 1;

    while (flag != 0) {
        parse(block, s);
        pop(s);
        Types *y = s->values[s->size-1];
        if (truthy(y) == 0) flag = 0;
    }
}



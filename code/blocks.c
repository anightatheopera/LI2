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
 * Executa um bloco ao elemento no topo da stack
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void exec_block (Stack *s, char *block) {
    char *b = calloc (strlen(block), sizeof(char));
    strcpy(b, block);
    b++;
    b[strlen(b)-1] = '\0';

    parse(b, s);
}

/**
 * Executa um bloco a uma string
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param n String onde será implementado o bloco
 */
void string_block (Stack *s, char *block, char *n) {
    char *new = calloc (10240, sizeof(char));
    Stack  *s2 = stackinit(100);
    s2->var = s->var;

    for (long i = 0; i<(long)strlen(n); i++) {
        push(s2, initChar(n[i]));
        exec_block(s2, block);
        pop(s2);
    }
    for (long k = 0; k < s2->size; k++) {
        Types *y = s2->values[k];
        conv_string(y);
        strcat(new, y->string);
        free(y);
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
    array->var = s->var;
    
    for (long i = 0; i<(n->size); i++) {
        Stack *s2 = stackinit(100);
        s2->var = s->var;
        push(s2, n->values[i]);
        exec_block(s2, block);
        for (long k = 0; k < s2->size-1; k++) {
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
    char *new = calloc (strlen(w->string) + 1, sizeof(char));
    for (long i = 0, k=0; i<(int)strlen(w->string); i++)
        if (w->string[i] != '0'){ 
            new[k] = n[i]; k++; 
        }

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
    Stack *array = stackinit(n->size);
    array->var = s->var;
    
    for (int i = 0; i<(n->size); i++) {
        Stack *s2 = stackinit(10);
        s2->var = s->var;
        Types* y = copy_value(s, n->values[i]);
        push(s2, n->values[i]);
        exec_block(s2, block);
        if (truthy(s2->values[0]) == 1) push(array,y);
        free(s2);
    }

    free(n);
    push(s, initArray(array));
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
    Stack *s2 = stackinit(3);
    s2->var = s->var;
    push(s2, n->values[0]);
    
    for (int i = 1; i<n->size; ++i) {
        Types *x = n->values[i];
        push(s2, x);
        exec_block(s2, block);
        pop(s2);
    }
    push(s, s2->values[0]);
    free(s2);
    free(n);
}

/**
 * Operação sort de um bloco
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void sort_block (Stack *s, char *block) {
    Stack *s2 = stackinit(100);
    s2->var = s->var;
    long count = s->size;
    
    for (long i = 0; i<count; i++) {
        Types *y = copy_value(s, s->values[i]);
        push(s2, y);
        exec_block(s2, block);
        pop(s2);
    }
    Types *temp1;
    Types *temp2;
    for (long j = 0; j < count; j++) {
      for (long k = j + 1; k < count; k++) {
          if(big_op(s2->values[k], s2->values[j]) == 1) {
            temp1 = s->values[j];
            s->values[j] = s->values[k];
            s->values[k] = temp1;
            temp2 = s2->values[j];
            s2->values[j] = s2->values[k];
            s2->values[k] = temp2;
          }
      }
    }
    free(s2);
}

/**
 * Operação de sort com bloco num array/string
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void sort_all (Stack *s, char *block) {
    Types *x = pop(s);
    if (x->type == array) { sort_block(x->array, block); push(s, x); }
    else { push(s, x); sort_block(s, block); }
}

/**
 * Aplicação de um bloco enquanto deixar um truthy no topo da stack
 * 
 * @param s A stack
 * @param block Bloco a executar
 */
void w_block (Stack *s, char *block) {
    int flag = 1;

    while (flag == 1) {
        exec_block(s, block);
        pop(s);
        Types *y = pop(s);
        if (truthy(y) == 0) flag = 0; 
    }
}



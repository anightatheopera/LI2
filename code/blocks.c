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
    Types *y = pop(s);
    Stack  *s2 = stackinit(100);

    push(s2, y);
    block++;
    block[strlen(block)-1] = '\0';

    parse(block, s2);
    
    for (int i = 0; i < s2->size-1; i++)
        push(s, s2->values[i]);
    free(s2);
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
    
    block++;
    block[strlen(block)-1] = '\0';
    

    for (int i = 0; i<(int)strlen(n); i++) {
        Stack  *s2 = stackinit(100);
        push(s2, initChar(n[i]));
        parse(block, s2);
        for (int k = 0; k < s2->size-1; k++) {
            Types *y = s2->values[k];
            conv_string(y);
            strcat(new, y->string);
        }
        free(s2);
    }

    push(s, initString(new));
}

/**
 * @brief Executa um bloco a um array
 * 
 * @param s A stack
 * @param block Bloco a executar
 * @param n Array onde será implementado o bloco
 */
void array_block (Stack *s, char *block, Stack *n) {
    Stack *array = stackinit(100);
    block++;
    block[strlen(block)-1] = '\0';
    
    for (int i = 0; i<n->size; i++) {
        Stack  *s2 = stackinit(100);
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

void map_block (Stack *s, char *block, Types *x) {
    if (x->string) string_block(s, block, x->string);
    else array_block(s, block, x->array);
}

/**
 * @brief Operação filter com bloco para string
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
 * @brief Operação filter com bloco para array
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
 * @brief Operação filter com bloco para strings e arrays
 * 
 * @param s A stack
 * @param block Bloco a executar como filter
 */
void filter_block (Stack* s, char *block) {
    Types *y = pop(s);
    if (y->string) filter_string(s, block, y->string);
    else filter_array(s, block, y->array);
}

void fold_array (Stack *s, char *block, Stack *n) {
    Stack *array = stackinit(100);
    block++;
    block[strlen(block)-1] = '\0';
    block[strlen(block)-2] = '\0';
    
    for (int i = 0; i<n->size; i++) {
        push(array, n->values[i]);
        parse(block, array);
    }

    free(n);
    push(s, initArray(array));
}
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


void filter_string (Stack *s, char *block, char *n) {
    char *new = calloc (1024, sizeof(char));
    block++;
    block[strlen(block)-1] = '\0';

    for (int i = 0, k = -1; i<(int)strlen(n); i++) {
        Stack  *s2 = stackinit(100);
        push(s2, initChar(n[i]));
        parse(block, s2);
        if (s2->values[i] != NULL) new[k++] = n[i-1];
        free(s2);
    }
    push(s, initString(new));
}

void filter_array (Stack *s, char *block, Stack *n) {
    Stack *array = stackinit(100);
    block++;
    block[strlen(block)-1] = '\0';
    
    for (int i = 0; i<n->size; i++) {
        Stack  *s2 = stackinit(100);
        push(s2, n->values[i]);
        parse(block, s2);
        Types *y = s2->values[i];
        if (y->number == 1) push(array, n->values[i]);
        free(s2);
    }

    free(n);
    push(s, initArray(array));
}

void filter_block (Stack* s, char *block) {
    Types *y = pop(s);
    if (y->string) filter_string(s, block, y->string);
    else filter_array(s, block, y->array);
}

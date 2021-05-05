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
    
    push(s, s2->values[0]);
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
        Types *y = s2->values[0];
        conv_string(y);
        strcat(new, y->string);
        free(s2);
    }

    push(s, initString(new));
}


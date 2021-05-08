/**
 * @file strings.c
 * @brief Este ficheiro contem as funções em strings
 * 
 */
#include "strings.h"
#include <string.h>
#include <stdlib.h>
#include "equations.h"
#include <stdio.h>

/**
 * Concatenação de strings
 * 
 * @param s A stack
 * @param y String a concatenar com x
 * @param x String a concatenar com y
 */
void cat_string (Stack *s, Types *y, Types *x){
    strcat(x->string, y->string);
	push(s, x); 
}

/**
 * Cria um certo número de réplicas de uma string
 * 
 * @param s A stack
 * @param y Número de réplicas
 * @param x String a replicar
 */
void replicate_string (Stack *s, int y, Types *x) {
    char *newS = calloc (strlen(x->string) * y, sizeof(char));
    while(y >  0) {
        strcat(newS, x->string);
        y--;
    }
    push(s, initString(newS));
}

/**
 * Remove o primeiro char de uma string e adiciona o à stack
 * 
 * @param s A stack
 * @param y String a remover o primeiro char
 */
void first_string (Stack *s, Types *y) {
    char c = y->string[0];
    y->string++;
    push(s, y);
    push(s, initChar(c));
}

/**
 * Remove o último char de uma string e adiciona o à stack
 * 
 * @param s A stack
 * @param y String a remover o último char
 */
void last_string (Stack *s, Types *y) {
    int size = strlen(y->string);
    char c = y->string[size-1];
    y->string[size-1] = '\0';
    push(s, y);
    push(s, initChar(c));
}

/**
 *  Procura o indice de uma substring numa string, caso a substring não exista na string coloca -1 na stack
 * 
 * @param s A stack
 * @param y Substring a procurar
 * @param x String
 */
void substring (Stack *s, Types *y, Types *x) {
    char *substring = strstr(x->string, y->string);
    if (substring != NULL) push(s, initNumber(substring - x->string));
    else push(s, initNumber(-1));
}

/**
 * Coloca na stack um char de uma string por indice
 * 
 * @param s A stack
 * @param y Indice
 * @param x String
 */
void index_string (Stack *s, Types *y, Types *x) {
    int i=0;
    if (y->string) {if (strcmp(y->string, x->string) == 0) i = 1;}
    else { 
        if (y != NULL) i = y->number;
        push(s, initChar(x->string[i]));
    }
}

/**
 * Coloca na stack uma string com os primeiros y chars da string inicial no topo da stack
 * 
 * @param s A stack
 * @param y Número de elementos
 * @param x String inicial
 */
void init_string (Stack *s, Types *y, Types *x) {
    int i=0;
    char *new = calloc(y->number, sizeof(char));
    for (i=0; i<y->number; i++) new[i] = x->string[i];
    new[i] = '\0';
    push(s, initString(new));
}

/**
 * Coloca na stack uma string com os últimos y chars da string inicial no topo da stack
 * 
 * @param s A stack
 * @param y Número de elementos
 * @param x String inicial
 */
void tail_string (Stack *s, Types *y, Types *x) {
    x->string += ((int)strlen(x->string)-y->number);
    push(s, x);
}


/**
 * Separa a string por uma substring e devolve um array com as strings
 * 
 * @param s A stack
 * @param y Subtring
 * @param x String
 */
void break_string (Stack *s, Types *y, Types *x) {
    if (y->type == string){
        Stack* st = stackinit(100);
        st->var = s->var;
        char* begin = x->string;
        char* end;
        while((end = strstr(begin, y->string)) != NULL){
            push(st, initString(strndup(begin, end - begin)));
            begin = strtok(x->string, y->string);
        }
        push(st, initString(begin));
        push(s, initArray(st));
    }
}

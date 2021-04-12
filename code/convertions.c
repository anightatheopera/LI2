/**
 * @file convertions.c
 * @brief Este ficheiro contem as funções de conversão de types
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "parser.h"
#include "types.h"
#include "convertions.h"

/**
 * @brief Compara dos elementos da stack e retorna o elemento cujo type é maior
 * 
 * @param x Elemento da stack a comparar
 * @param y Elemento da stack a comparar
 * @return Types* Elemento cujo type é maior
 */
Types *max_type(Types *x, Types *y) {
    if (x->type > y->type) return x;
    else return y; 
}

/**
 * @brief Compara dos elementos da stack e retorna o elemento cujo type é menor
 * 
 * @param x Elemento da stack a comparar
 * @param y Elemento da stack a comparar
 * @return Types* Elemento cujo type é menor
 */
Types *min_type(Types *x, Types *y) {
    if (x->type < y->type) return x;
    else return y; 
}

/**
 * @brief Converte um elemento da stack para um type diferente
 * 
 * @param x Type a converter
 * @param y Elemento a converter
 */
void converte(Diftypes x, Types *y) {
    char * str;
    int n;
    switch(x) {
        case string:
            switch(y->type) {
                case single:
                    str = calloc(2, sizeof(char));
                    sprintf(str, "%c", y->single);
                    y->string = str;
                    initString(y->string);
                    break;
                case number:
                    str = calloc(200000, sizeof(char));
                    sprintf(str, "%ld", y->number);
                    y->string = str;
                    initString(y->string);
                    break;
                case floats:
                    str = calloc(200000, sizeof(char));
                    sprintf(str, "%f", y->floats);
                    y->string = str;
                    initString(y->string);
                    break;
                default:
                    initString(y->string);
                    break;
            }  
        break;
        case single:
            switch(y->type){
                case number:
                    y->single = (char) y->number;
                    initChar(y->single);
                    break;
                case floats:
                    n = ((int) floor(y->floats));
                    y->single = (char) n;
                    initChar(y->single);
                    break;
                default:
                    initChar(y->single);
                    break;
            }
        break;
        case floats:
            switch (y->type) {
                case string:
                    y->floats = atof(y->string);
                    initFloat(y->floats);
                    break;
                case single:
                    y->floats = (double) y->single;
                    initFloat(y->floats);
                    break;
                case number:
                    y->floats = (double) y->number;
                    initFloat(y->floats);
                    break;
                default:
                    initFloat(y->floats);
                    break;
                }
        break;
        case number:
            switch(y->type) {
                case single:
                    y->number = (int) y->single;
                    initNumber(y->number);
                    break;
                case floats:
                    y->number = floor(y->floats);
                    initNumber(y->number);
                    break;
                default:
                    initNumber(y->number);
                    break;
            }
        break;       
    }
    y->type = x;       
}
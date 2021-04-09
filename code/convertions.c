#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "parser.h"
#include "types.h"
#include "convertions.h"

Types *max_type(Types *x, Types *y) {
    if (x->type > y->type) return x;
    else return y; 
}

Types *min_type(Types *x, Types *y) {
    if (x->type < y->type) return x;
    else return y; 
}

void converte(Types *x, Types *y) {
    char *str;
    int n;
    switch(x->type) {
        case string:
            switch(y->type) {
                case single:
                    str = calloc(2, sizeof(char));
                    sprintf(str, "%c", y->single);
                    y->string = str;
                    break;
                case number:
                    str = calloc(200000, sizeof(char));
                    sprintf(str, "%ld", y->number);
                    y->string = str;
                    break;
                case floats:
                    str = calloc(200000, sizeof(char));
                    sprintf(str, "%f", y->floats);
                    y->string = str;
                    break;
                default:
                    break;
            }  
        break;
        case single:
            switch(y->type){
                case number:
                    y->single = (char) y->number;
                    break;
                case floats:
                    n = ((int) floor(y->floats));
                    y->single = (char) n;
                    break;
                default:
                    break;
            }
        break;
        case floats:
            switch (y->type) {
                case string:
                    y->floats = atof(y->string);
                    break;
                case single:
                    y->floats = (double) y->single;
                    break;
                case number:
                    y->floats = (double) y->number;
                    break;
                default:
                    break;
                }
        break;
        case number:
            switch(y->type) {
                case single:
                    y->number = (int) y->single;
                    break;
                case floats:
                    y->number = floor(y->floats);
                    break;
                default:
                    break;
            }
        break;       
    }
    y->type = x->type;       
}


/**
 * Esta função converte um elemento para inteiro, se conseguir, adiciona-os à mesma
 * @param s A stack
 * @param str A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
/*
int toInt(Stack* s, char* str){
    if(strcmp("i", str)==0){
        Types* t = pop(s);
        switch(t->type){
            case string:               ;
                int a = atoi(t->string);
                push(s,initNumber(a));
                break;
            case single:               ;
                int b = (int) t->single;
                push(s,initNumber(b));
                break;
            case number:         ;
                int c = t->number;
                push(s,initNumber(c));
                break;
            case floats:                ;
                int d = floor(t->floats);
                push(s,initNumber(d));
                break;
        }   
        return 1;
    }
    else return 0;

}*/

/**
 * Esta função converte um elemento para número decimal, se conseguir, adiciona-os à mesma
 * @param s A stack
 * @param str A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
/*
int toFloat(Stack* s, char* str){
    if(strcmp("f", str)==0){
        Types* t = pop(s);
        switch(t->type){
            case string:                 ;
                double a = atof(t->string);
                push(s,initFloat(a));
                break;
            case single:                   ;
                double b = (double) t->single;
                push(s,initFloat(b));
                break;
            case number:                   ;
                double c = (double) t->number;
                push(s,initFloat(c));
                break;
            case floats:           ;
                double d = t->floats;
                push(s,initFloat(d));
                break;
        }   
        return 1;
    }
    else return 0;

}*/

/**
 * Esta função converte um elemento para um caracter, se conseguir, adiciona-os à mesma
 * @param s A stack
 * @param str A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
/*
int toChar(Stack* s, char* str){
    if(strcmp("c", str)==0){
        Types* t = pop(s);
        switch(t->type){
            case string:            ;
                push(s,initString(t->string));
                break;
            case single:          ;
                char b = t->single;
                push(s,initChar(b));
                break;
            case number:                 ;
                char c = (char) t->number;
                push(s,initChar(c));
                break;
            case floats:                                ;
                int n = ((int) floor(t->floats));
                char d = (char) n;
                push(s,initChar(d));
                break;
        }   
        return 1;
    }
    else return 0;
}*/

/**
 * Esta função converte um elemento para uma string, se conseguir, adiciona-os à mesma
 * @param s A stack
 * @param str A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
/*int toString(Stack* s, char* str){
    if(strcmp("s", str)==0){
        Types* t = pop(s);
        switch(t->type){
            case string:                     ;
                push(s,initString(t->string));
                break;
            case single:                         ;
                char* x = calloc(2, sizeof(char));
                sprintf(x, "%c", t->single);
                push(s,initString(x));
                break;
            case number:                         ;
                char* y = calloc(200000, sizeof(char));
                sprintf(y, "%d", t->number);
                push(s,initString(y));
                break;
           case floats:                         ;
                char* z = calloc(200000, sizeof(char));
                sprintf(z, "%f", t->floats);
                push(s,initString(z));
                break;
                break;
        }   
        return 1;
    }
   else return 0;
} */
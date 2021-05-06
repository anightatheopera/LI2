#include "strings.h"
#include <string.h>
#include <stdlib.h>

void cat_string (Stack *s, Types *y, Types *x){
    strcat(x->string, y->string);
	push(s, x); 
}

void replicate_string (Stack *s, Types *y, Types *x) {
    char newS[strlen(x->string) * y->number];
    while(y->number >  0) {
        strcat(newS, x->string);
        y->number--;
    }
    push(s, initString(newS));
}

void first_string (Stack *s, Types *y) {
    char c = y->string[0];
    y->string++;
    push(s, y);
    push(s, initChar(c));
}

void last_string (Stack *s, Types *y) {
    int size = strlen(y->string);
    char c = y->string[size-1];
    y->string[size-1] = '\0';
    push(s, y);
    push(s, initChar(c));
}

void substring (Stack *s, Types *y, Types *x) {
    char *substring = strstr(x->string, y->string);
    if (substring != NULL) push(s, initNumber(substring - x->string));
    else push(s, initNumber(-1));
}

void index_string (Stack *s, Types *y, Types *x) {
    int i=0;
    if (y->string) {if (strcmp(y->string, x->string) == 0) i = 1;}
    else { 
        if (y != NULL) i = y->number;
        push(s, initChar(x->string[i]));
    }
}

void init_string (Stack *s, Types *y, Types *x) {
    int i=0;
    char *new = calloc(y->number, sizeof(char));
    for (i=0; i<y->number; i++) new[i] = x->string[i];
    new[i] = '\0';
    push(s, initString(new));
}

void tail_string (Stack *s, Types *y, Types *x) {
    x->string += ((int)strlen(x->string)-y->number);
    push(s, x);
}


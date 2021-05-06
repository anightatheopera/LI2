#include "arrays.h"
#include <stdlib.h>

void cat_array (Stack *s, Types *y, Types *x){
    Stack *array = stackinit(100);
    for (int i=0; i < x->array->size; i++) push(array, x->array->values[i]);
    for (int i=0; i < y->array->size; i++) push(array, y->array->values[i]);
    push(s, initArray(array));
}

void replicate_array (Stack *s, Types *y, Types *x) {
    Stack *array = stackinit(100);
    while (y->number > 0 ) {	
        for (int i=0; i < x->array->size; i++) push(array, x->array->values[i]);
        y->number --;
    }
    push(s, initArray(array));
}

void first_array (Stack *s, Types *y) {
    Stack *array = stackinit(y->array->size);
    Types *x = y->array->values[0];
    for (int i=1; i< y->array->size; i++) {
        push(array, y->array->values[i]);
    }
    push(s, initArray(array));
    push(s, x);
    free(y);
}

void last_array (Stack *s, Types *y) {
    Types *x = pop(y->array);
	push(s, y);
    push(s, x);
}

void include_stack (Stack *s, Types *y) {
    for (int i=0; i < y->array->size; i++) push(s, y->array->values[i]);
}

void index_array(Stack *s, Types *y, Types *x) {
    push(s, x->array->values[y->number]);
}

void init_array(Stack *s, Types *y, Types *x)  {
    int i=0;
    Stack *array = stackinit(100);
    for (i=0; i<y->number; i++) push(array, x->array->values[i]);
    push(s, initArray(array));
}

void tail_array(Stack *s, Types *y, Types *x)  {
    Stack *array = stackinit(100);
    for (; y->number>0; y->number--) push(array, x->array->values[(x->array->size)-(y->number)]);
    push(s, initArray(array));
}

void range_array (Stack *s, Types *y) {
    Stack *array = stackinit(100);
    for (int n = 0; n < y->number; n++) push(array, initNumber(n));
    push(s, initArray(array));
}
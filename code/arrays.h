#ifndef ARRAYS_H 
#define ARRAYS_H
#include "stack.h"

void cat_array (Stack *, Types *, Types *);
void add_array (Stack *, Types *, Types *);
void replicate_array (Stack *, int, Types *); 
void first_array (Stack *, Types *); 
void last_array (Stack *, Types *); 
void include_stack (Stack *, Types *); 
void index_array(Stack *, Types *, Types *); 
void init_array(Stack *, Types *, Types *);  
void tail_array(Stack *, Types *, Types *); 
void range_array (Stack *, Types *);
void create_array (Stack *, Stack *);

#endif
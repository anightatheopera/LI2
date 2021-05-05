#ifndef EQUATIONS_H 
#define EQUATIONS_H
#include "stack.h"

int plus_ops(Stack *, char*);
int minus_ops(Stack *, char*);
int mult_ops(Stack *, char*);
int div_ops(Stack *, char*);
int mod_ops(Stack *, char*);
int inc_ops(Stack *, char*);
int dec_ops(Stack *, char*);
int pow_ops(Stack *, char*);
int and_ops(Stack *, char*);
int or_ops(Stack *, char*);
int xor_ops(Stack *, char*);
int not_ops(Stack *, char*);
int double_ops(Stack *, char*);
int pop_ops(Stack *, char*);
int swap2_ops(Stack *, char*);
int swap3_ops(Stack *, char*);
int copy_n_ops(Stack *, char*);
int toInt(Stack *, char*);
int toFloat(Stack *, char*);
int toString(Stack *, char*);
int toChar(Stack *, char*);
int print_top(Stack *, char*);
int stackAdderChar(Stack *, char*);
int stackAdderString(Stack *, char*);
int stackAdderFloat(Stack *, char*);
int stackAdderBlock(Stack *, char*);
int stackAdderInt(Stack *, char*);
void stackAdderArray(Stack *, char*);
int read_line (Stack *, char *);
int arraylen (int *);
int read_all(Stack *, char *);
int range(Stack *, char *);
int new_var(Stack *, char *);
int eq(Stack *, char *);
int lesser(Stack *, char *);
int bigger(Stack *, char *);
int not(Stack *, char *);
int and(Stack *, char *);
int or(Stack *, char *);
int push_lesser(Stack *, char *);
int arithmetic(Stack *, char *);
int logic(Stack *, char *);
int stack_man(Stack *, char *);
int arrays_strings(Stack *, char *);
int input_output(Stack *, char *);
int convertions(Stack *, char *);
int compute_stack(Stack *, char *);


#endif
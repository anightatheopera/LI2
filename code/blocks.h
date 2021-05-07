#ifndef BLOCKS_H 
#define BLOCKS_H

void exec_block (Stack *, char *);
void string_block (Stack *, char *, char *);
void array_block (Stack *, char *, Stack *);
void filter_block(Stack *, char *);
void filter_string(Stack *, char *, char  *);
void filter_array(Stack *, char *, Stack *);
void fold_array(Stack *, char *, Stack *);
void map_block(Stack *, char *, Types *);
void sort_block(Stack *, char *);
void w_block(Stack *, char *);

#endif
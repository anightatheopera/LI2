#ifndef STACK2_H 
#define STACK2_H

typedef struct stack {
    void** values;
    int allocsize;
    int size;
} Stack;

Stack* stackinit(int capacity);
void* pop(Stack*);
void push(Stack*, void*);

#endif
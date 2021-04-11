#ifndef TYPES_H 
#define TYPES_H

typedef enum { string = 4, single = 3, floats = 2, number = 1} Diftypes;

typedef struct types {
    Diftypes type;
    char* string;
    long number;
    double floats;
    char single;
} Types;

Types *init(Diftypes);
Types *initNumber(int);
Types *initChar(char);
Types *initString(char*);
Types *initFloat(double);

#endif
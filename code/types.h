#ifndef TYPES_H 
#define TYPES_H

enum diftype {
    string,
    single,
    number,
    floats
};

typedef struct types {
    char* string;
    char single;
    int number;
    double floats;
    enum diftype type;
} Types;

Types* init(enum diftype d);
Types* initNumber(int n);
Types* initChar(char n);
Types* initString(char* n);
Types* initFloat(double n);

#endif


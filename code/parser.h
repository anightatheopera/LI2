#ifndef PARCER_H 
#define PARCER_H
#include "equations.h"

void parse(char *, Stack *);
char *get_token(char *, char **);
char *get_block(char *, char **);
char *get_delimited(char *, char *, char **);

#endif
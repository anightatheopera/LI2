#ifndef CONVERTIONS_H 
#define CONVERTIONS_H
#include "stack.h"
#include "types.h"

Types *max_type(Types *, Types *);
Types *min_type(Types *, Types *);
void converte(Diftypes, Types *);
void conv_int(Types *);
void conv_char(Types *);
void conv_string(Types *);
void conv_float(Types *);

#endif 
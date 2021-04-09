/** 
 * @file Este ficheiro contêm as funções relacionadas ao parser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "parser.h"
#include "types.h"
#include "convertions.h"

/** 
 * \brief Esta é a função que vai fazer o parse de uma linha.
 *
 *
 * @param line Corresponde à linha que foi lida e da qual se vai fazer o parse.
 * \info Implementa expressões matemáticas de acordo com a leitura dos tokens (elementos do input)
 * 
 */

void parse(char *line) {

	char *delims = " \t\n";
	Stack *s = stackinit(100);

	for(char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {

		/*char *sobra;
		Types *val_i = strtol(token, &sobra, 100);*/

		if(strcmp (token, "\0") == 0) print_stack(s);
		else if(strcmp (token, "+") == 0){
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number + x->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats + x->floats));
			else if (y->type == single)
				push(s, initChar(y->single + x->single));

			free(x);
			free(y);

		} else if(strcmp(token, "-") == 0){
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number - x->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats - x->floats));
			else if (y->type == single)
				push(s, initChar(y->single - x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "*") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number * x->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats * x->floats));
			else if (y->type == single)
				push(s, initChar(y->single * x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "/") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number / x->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats / x->floats));
			else if (y->type == single)
				push(s, initChar(y->single / x->single));
			
			free(x);
			free(y);
			
		}else if (strcmp (token, "%") == 0) {      
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number % x->number));
			//else if (y->type == floats)
			//	push(s, initFloat(y->floats % x->floats));
			else if (y->type == single)
				push(s, initChar(y->single % x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "(") == 0) {       
			Types *y = pop(s);

			if (y->type == number)
				push(s, initNumber(y->number + 1));
			else if (y->type == floats)
				push(s, initFloat(y->floats + 1.0));
			else if (y->type == single)
				push(s, initChar(y->single + 1));

			free(y);

		}else if (strcmp (token, ")") == 0) {      
			Types *y = pop(s);

			if (y->type == number)
				push(s, initNumber(y->number - 1));
			else if (y->type == floats)
				push(s, initFloat(y->floats - 1.0));
			else if (y->type == single)
				push(s, initChar(y->single - 1));
			
			free(y);

		}else if (strcmp (token, "#") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(pow (y->number, x->number)));
			else if (y->type == floats)
				push(s, initFloat(pow (y->floats, x->floats)));
			else if (y->type == single)
				push(s, initChar(pow (y->single, x->single)));

			free(x);
			free(y);

		}else if (strcmp (token, "&") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number & x->number));
			//else if (y->type == floats)
			//	push(s, initFloat(y->floats & x->floats));
			else if (y->type == single)
				push(s, initChar(y->single & x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "^") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number ^ x->number));
			//else if (y->type == floats)
			//	push(s, initFloat(y->floats ^ x->floats));
			else if (y->type == single)
				push(s, initChar(y->single ^ x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "~") == 0) {       
			Types *y = pop(s);

			if (y->type == number)
				push(s, initNumber(~ y->number));
			//else if (y->type == floats)
			//	push(s, initFloat(~ y->floats));
			else if (y->type == single)
				push(s, initChar(~ y->single));

			free(y);

		}else if (strcmp (token, "|") == 0) {       
			Types *y = pop(s);
			Types *x = pop(s);
			Types *maxt = max_type(x, y);
			Types *mint = min_type(x, y);

			converte(maxt, mint);

			if (y->type == number)
				push(s, initNumber(y->number | x->number));
			//else if (y->type == floats)
			//	push(s, initFloat(y->floats | x->floats));
			else if (y->type == single)
				push(s, initChar(y->single | x->single));

			free(x);
			free(y);

		}else if (strcmp (token, "_") == 0) {
			Types *y = pop(s);

			if (y->type == number) {
				push(s, initNumber(y->number));
				push(s, initNumber(y->number));

			} else if (y->type == floats) {
				push(s, initFloat(y->floats));
				push(s, initFloat(y->floats));

			} else if (y->type == single) {
				push(s, initChar(y->single));
				push(s, initChar(y->single));

			} else if (y->type == string) {
				push(s, initString(y->string));
				push(s, initString(y->string));
			}

			free(y);

		}else if (strcmp (token, ";") == 0) {
			pop(s);

		}else if (strcmp (token, "\\") == 0) {
			Types *y = pop(s);
			Types *x = pop(s);

			if (x->type == number)
				push(s, initNumber(x->number));
			else if (x->type == floats)
				push(s, initFloat(x->floats));
			else if (x->type == single)
				push(s, initChar(x->single));

			if (y->type == number)
				push(s, initNumber(y->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats));
			else if (y->type == single)
				push(s, initChar(y->single));

			free(x);
			free(y);

		}else if (strcmp (token, "@") == 0) {
			Types *z = pop(s);
			Types *y = pop(s);
			Types *x = pop(s);

			if (y->type == number)
				push(s, initNumber(y->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats));
			else if (y->type == single)
				push(s, initChar(y->single));
			else if (y->type ==string)
				push(s, initString(y->string));

			if (z->type == number)
				push(s, initNumber(z->number));
			else if (z->type == floats)
				push(s, initFloat(z->floats));
			else if (z->type == single)
				push(s, initChar(z->single));
			else if (y->type ==string)
				push(s, initString(y->string));

			if (x->type == number)
				push(s, initNumber(x->number));
			else if (x->type == floats)
				push(s, initFloat(x->floats));
			else if (x->type == single)
				push(s, initChar(x->single));
			else if (y->type ==string)
				push(s, initString(y->string));

			free(x);
			free(z);
			free(y);

		}else if (strcmp (token, "$") == 0) {
			Types *indice = pop(s);
			Types *y = s->values[top(s)->number - indice->number];
		
			if (y->type == number)
				push(s, initNumber(y->number));
			else if (y->type == floats)
				push(s, initFloat(y->floats));
			else if (y->type == single)
				push(s, initChar(y->single));

			free(indice);
			free(y);
		}
	free(s);
	}
}
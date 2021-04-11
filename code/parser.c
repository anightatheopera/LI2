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
#include "equations.h"


/** 
 * \brief Esta é a função que vai fazer o parse de uma linha.
 *
 *
 * @param line Corresponde à linha que foi lida e da qual se vai fazer o parse.
 * \info Implementa expressões matemáticas de acordo com a leitura dos tokens (elementos do input)
 * 
 */

void parse(char *line) {
	Stack *s = stackinit(100);

	for(char *token = strtok(line, " \t\n"); token != NULL; token = strtok(NULL, " \t\n")){
		
		char *sobra;
		int val_i = strtol(token, &sobra, 10);

		if(strlen (sobra) == 0)
			push(s, initNumber(val_i));

		else compute_stack(s, token);
	}
	print_stack(s);
	free(s);
}
/** 
 * @file parser.c
 * @brief Este ficheiro contêm as funções relacionadas com a inicialização da stack.
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
 * @brief Lê a linha de input e iniciliza a stack com os valores de input
 *
 * @param line Linha de input a ler
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
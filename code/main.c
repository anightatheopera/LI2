/** 
 * @file main.c
 * @brief Este ficheiro contem a main do guiao 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

/**
 * @brief Esta é a função principal do programa
 * 
 * @returns O valor 0
 */
int main(){
	Stack *s = stackinit(100);
	char line[10240];

	assert( fgets(line, 10240, stdin) != NULL);
	assert( line[strlen(line) - 1] == '\n'   );

	parse(line, s);
	print_stack(s);
	printf("\n");
  	free(s);
	return 0;
}
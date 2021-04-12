<<<<<<< HEAD
/** 
 * @file main.c
 * @brief Este ficheiro contem a main do guiao 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "parser.h"

int main(){
	char line[10240];

	assert( fgets(line, 10240, stdin) != NULL);
	assert( line[strlen(line) - 1] == '\n'   );

	parse(line);
	return 0;
=======
/** 
 * @file main.c
 * @brief Este ficheiro contem a main do guiao 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "parser.h"

/**
 * @brief Esta é a função principal do programa
 * 
 * @returns O valor 0
 */
int main(){
	char line[10240];

	assert( fgets(line, 10240, stdin) != NULL);
	assert( line[strlen(line) - 1] == '\n'   );

	parse(line);
	return 0;
>>>>>>> b433a1a47fd89e5e8ee164c878af69789843f139
}
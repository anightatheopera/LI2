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


char *get_token(char *line, char **rest) {
    int i=0;
    int size = strlen(line);
    char *token = calloc(size, sizeof(char));
    
    if (line[0] == ' ') {
      for ( i=0; i<size; i++) line[i] = line[i+1];
      line[i] = '\0';
    }
    
    for(i=0; line[i]!='\n' && line[i]!='\0' && line[i]!=' ' && line[i]!='\t' && i<size; i++)
      token[i] = line[i];
    
    if (token[0] == '\0') {
      token = NULL;
      free(token);
    }

    *rest = &line[i];

    return token;
}

/**
 * @brief Lê a linha de input e iniciliza a stack com os valores de input
 *
 * @param line Linha de input a ler
 */
void parse(char *line) {
	Stack *s = stackinit(100);
  char *token;
  char *rest = NULL;

  while((token = get_token(line, &rest))) {
    line = &(*rest);
    rest = NULL;
    compute_stack(s, token);
    free(token);
}
	print_stack(s);
	free(s);
}
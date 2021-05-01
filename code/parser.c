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
 * @brief Separa o token do resto do input
 * 
 * @param line Linha de input
 * @param rest Resto da linha
 * @return Devolve o token
 */
char *get_token(char *line, char **rest) {
    int i;
    int size = strlen(line);
    char *token = calloc(size, sizeof(char));
    
  for(i=0; line[i]!='\n' && line[i]!='\0' && line[i]!=' ' && line[i]!='\t' && i<size; i++)
      token[i] = line[i];

  if (token[0] == '\0') token = NULL;

  *rest = &line[i+1];

   return token;
}

/**
 * @brief Separa e devolve a parte do input que está delimitada por "\"\"" (string) ou por "[]" (array)
 * 
 * @param line Linha de input
 * @param seps Separadores "\"\"" ou "[]"
 * @param rest Resto da linha
 * @return Devolve o token como string ou array
 */
char *get_delimited(char *line, char *seps, char **rest) {
  int i;
  int size = strlen(line);
  char *token = calloc(size, sizeof(char));

  for(i=1; line[i] != seps[1]; i++) token[i-1] = line[i];
  token[i-1] = '\0';

  *rest = &line[i+1];
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

  while (line != NULL) {

    while ((line[0] == ' ' || line[0] == '\n') && line[1] != '\0') line++;

    if (line[0] == '\"') {
      token = get_delimited(line, "\"\"", &rest);
      if (token != NULL) stackAdderString(s, token);


    //}else if (line[0] == '[') {
    //  token = get_delimited(line, "[]", &rest);
    //  stackAdderArray?
    
    } else {
      token = get_token(line, &rest);
      if (token != NULL) compute_stack(s, token);

    }

    line = &(*rest);
    rest = NULL;
    if (token == NULL || line[0] == '\0' || line[0] == '\n') line = NULL;

  }
	print_stack(s);
	free(s);
}
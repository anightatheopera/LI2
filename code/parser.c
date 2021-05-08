/** 
 * @file parser.c
 * @brief Este ficheiro contêm as funções relacionadas com a inicialização da stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equations.h"


/**
 * Separa o token do resto do input
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
 * Separa e devolve a parte do input que está delimitada por "[]" (array)
 * 
 * @param line Linha de input
 * @param rest Resto da linha
 * @return Devolve o token como string ou array
 */
char *get_array(char *line, char **rest) {
  int i, f, l;
  int size = strlen(line);
  char *token = calloc(size, sizeof(char));

  for (i=1, f=1, l=0; l < f; ++i) {
    if (line[i] == '[') ++f;
    if (line[i] == ']') ++l;
    token[i-1] = line[i];
  }
  token[i - 2] = '\0';

  *rest = &line[i];
  return token;
}

/**
 * Get the string object
 * 
 * @param line Linha de input
 * @param rest Resto da linha
 * @return Devolve o token como string
 */
char *get_string(char *line, char **rest) {
  int i, j;
  int size = strlen(line);
  char *token = calloc(size, sizeof(char));

  for(i=1, j=0; line[i] != '\"'; j++, i++) token[j] = line[i];
  token[j] = '\0';

  *rest = &line[i+1];
  return token;
}
/**
 * Separa e devolve a parte do input que está delimitada por "{ }" e adiciona à stack como um bloco
 * 
 * @param line Linha de input
 * @param rest Resto da linha
 * @return Devolve o token como bloco
 */
void *get_block(char *line, char **rest) {
  int i;
  int size = strlen(line);
  char *token = calloc(size, sizeof(char));

  for(i=0; line[i] != '}'; i++) token[i] = line[i];
  token[i] = '}';
  token[i+1] = ' ';

  *rest = &line[i+1];
  return token;
}

/**
 * Lê a linha de input e adiciona os valores de input à respetiva stack
 *
 * @param line Linha de input a ler
 * @param s A stack
 */
void parse(char *line, Stack *s) {
  char *token;
  char *rest = NULL;

  while (line != NULL) {
    while ((line[0] == ' ' || line[0] == '\n') && line[1] != '\0') line++;

    if (line[0] == '\"') {
      token = get_string(line, &rest);
      if (token != NULL) stackAdderString(s, token);


    }else if (line[0] == '[') {
      token = get_array(line, &rest);
      if (token != NULL) stackAdderArray(s, token);

    } else if (line[0] == '{') {
      token = get_block(line, &rest);
      if (token != NULL) stackAdderBlock(s, token);

    } else {
      token = get_token(line, &rest);
      if (token != NULL) compute_stack(s, token);

    }

    line = &(*rest);
    rest = NULL;
    if (token == NULL || line[0] == '\0' || line[0] == '\n') line = NULL;

  }
}
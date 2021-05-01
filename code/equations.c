/** 
 * @file equations.c
 * Este ficheiro contem todas as equações a implementar na stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "stack.h"
#include "parser.h"
#include "types.h"
#include "convertions.h"

/**
 * Soma os dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int plus_ops(Stack *s, char *token){
    if(strcmp (token, "+") == 0){
            Types *y = pop(s);
            Types *x = pop(s);
            Types *maxt = max_type(x, y);
            Types *mint = min_type(x, y);

            converte(maxt->type, mint);

            if (y->type == number)
                push(s, initNumber(y->number + x->number));
            else if (y->type == floats)
                push(s, initFloat(y->floats + x->floats));
            else if (y->type == single)
                push(s, initChar(y->single + x->single));
			else if (y->type == string) {
				int size = strlen(x->string) + strlen(y->string);
				for(int i = strlen(x->string), j=0; i <= size; i++, j++) x->string[i] = y->string[j];
				push(s, initString(x->string));
			}

            return 1;
    }
    else return 0;
}

/**
 * Subtrai os dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int minus_ops(Stack *s, char *token) {
	if (strcmp(token, "-") == 0){
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(x->number - y->number));
		else if (y->type == floats)
			push(s, initFloat(x->floats - y->floats));
		else if (y->type == single)
			push(s, initChar(x->single - y->single));

		return 1;

	} else return 0;
}

/**
 * Multiplica os dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int mult_ops(Stack *s, char *token){
	if (strcmp (token, "*") == 0){       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(y->number * x->number));
		else if (y->type == floats)
			push(s, initFloat(y->floats * x->floats));
		else if (y->type == single)
			push(s, initChar(y->single * x->single));
		else if (y->type == string){
			int size = strlen(x->string);
			char new[size + y->number];

			converte (number, y);
			for(int j = 0; j < y->number; j++) {
				for (int i = 0; i < size; i++) new[j*size + i] = x->string[i];
			}
			if (y->number == 0) new[0] = '\0';
			push(s, initString(new));
		}
		return 1;
		
	} else return 0;
}

/**
 * Divide os dois elementos no topo da stack, no caso de strings é feita a separação do segundo elemento pela string no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int div_ops(Stack *s, char *token){
	if (strcmp (token, "/") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(x->number / y->number));
		else if (y->type == floats)
			push(s, initFloat(x->floats / y->floats));
		else if (y->type == single)
			push(s, initChar(x->single / y->single));
		else if (y->type == string)
			push(s, initString(strtok(x->string, y->string)));
		
		return 1;

	} else return 0;
}

/**
 * Calcula o módulo dos dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int mod_ops(Stack *s, char *token){	
	if (strcmp (token, "%") == 0) {      
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(x->number % y->number));
		//else if (x->type == floats)
		//	push(s, initFloat(x->floats % y->floats));
		else if (y->type == single)
			push(s, initChar(x->single % y->single));

		return 1;

	} else return 0;
}

/**
 * Decrementa o elemento no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int inc_ops(Stack *s, char *token){
	if (strcmp (token, "(") == 0) {       
		Types *y = pop(s);

		if (y->type == number)
			push(s, initNumber(y->number - 1));
		else if (y->type == floats)
			push(s, initFloat(y->floats - 1.0));
		else if (y->type == single)
			push(s, initChar(y->single - 1));
		else if (y->type == string) {
			int size = strlen(y->string), i = 0;
			for (i = 0; i < size-1; i++) y->string[i] = y->string[i+1];
			y->string[i] = '\0';
			push(s, initString(y->string));
			push(s, initChar(y->string[0]));
		}

		return 1;
	} else return 0;
}

/**
 * Incrementa o elemento no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int dec_ops(Stack *s, char *token){
	if (strcmp (token, ")") == 0) {      
		Types *y = pop(s);

		if (y->type == number)
			push(s, initNumber(y->number + 1));
		else if (y->type == floats)
			push(s, initFloat(y->floats + 1.0));
		else if (y->type == single)
			push(s, initChar(y->single + 1));
		else if (y->type == string) {
			int size = strlen(y->string);
			y->string[size-1] = '\0';
			push(s, initString(y->string));
			push(s, initChar(y->string[size-1]));
		}		
		return 1;

	} else return 0;
}

/**
 *  Calcula a potência entre os dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int pow_ops(Stack *s, char *token){
	if (strcmp (token, "#") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);
	
		converte(maxt->type, mint);
	
		if (y->type == number)
			push(s, initNumber(pow (x->number, y->number)));
		else if (y->type == floats)
			push(s, initFloat(pow (x->floats, y->floats)));
		else if (y->type == single)
			push(s, initChar(pow (x->single, y->single)));
		else if (y->type == string) {
			char *substring = strstr(x->string, y->string);
			if (substring != NULL) push(s, initNumber(substring - x->string));
			else push(s, initNumber(-1));
		}
	
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função "and" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token A string
 *
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int and_ops(Stack *s, char *token){
	if (strcmp (token, "&") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(y->number & x->number));
		//else if (y->type == floats)
		//	push(s, initFloat(y->floats & x->floats));
		else if (y->type == single)
			push(s, initChar(y->single & x->single));

		return 1;
	
	} else return 0;
}


/**
 * Esta função aplica a função "xor" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int xor_ops(Stack *s, char *token){
	if (strcmp (token, "^") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(y->number ^ x->number));
		//else if (y->type == floats)
		//	push(s, initFloat(y->floats ^ x->floats));
		else if (y->type == single)
			push(s, initChar(y->single ^ x->single));

		return 1;

	} else return 0;
}

/**
 * Esta função aplica a função "not" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */

int not_ops(Stack *s, char *token){
		if (strcmp (token, "~") == 0) {       
			Types *y = pop(s);

			if (y->type == number)
				push(s, initNumber(~ y->number));
			//else if (y->type == floats)
			//	push(s, initFloat(~ y->floats));
			else if (y->type == single)
				push(s, initChar(~ y->single));

			return 1;

		} else return 0;
}

/**
 * Esta função aplica a função "or" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 *
 *  @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int or_ops(Stack *s, char *token){
	if (strcmp (token, "|") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number)
			push(s, initNumber(y->number | x->number));
		//else if (y->type == floats)
		//	push(s, initFloat(y->floats | x->floats));
		else if (y->type == single)
			push(s, initChar(y->single | x->single));
		return 1;

	} else return 0;
}

/**
 * Duplica o elemento no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int double_ops(Stack *s, char *token){
	if (strcmp (token, "_") == 0) {
		Types *y = pop(s);

		if (y->type == string){
			Types *x = initString(y->string);
			strcpy(x->string, y->string);
			push(s, x);

		}else push(s, y);
		
		push(s, y);
		return 1;
	
	}else return 0;
}

/**
 * Retira o elemento no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int pop_ops(Stack *s, char *token){
	if (strcmp (token, ";") == 0) {
		pop(s);
		return 1;

	} else return 0;
}

/**
 * Troca os dois elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int swap2_ops(Stack *s, char *token){
	if(strcmp("\\", token)==0){
        Types* x = pop(s);
        Types* y = pop(s);

        push(s,x);
        push(s,y);
        return 1;
    }
    else return 0;
}

/**
 * Troca os três elementos no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int swap3_ops(Stack *s, char *token){
	if(strcmp("@", token)==0){
        Types* x = pop(s);
        Types* y = pop(s);
        Types* z = pop(s);

        push(s,y);
        push(s,x);
        push(s,z);
        return 1;
    }
    else return 0;
}

/**
 * Copia o n-ésimo elemento da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int copy_n_ops(Stack *s, char *token){
	if (strcmp (token, "$") == 0) {
		Types *indice = pop(s);
		Types *y = s->values[(s->size - 1) - indice->number];

		push(s, y);
		return 1;
	} else return 0;
}

/**
 * Converte o elemento no topo da stack para inteiro
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int toInt(Stack *s, char *token){
	if(strcmp("i", token)==0){
		Types *y = pop(s);

		conv_int(y);
		push(s, y);
		return 1;

	} else return 0;
}

/**
 * Converte o elemento no topo da stack para float
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int toFloat(Stack *s, char *token){
    if(strcmp("f", token)==0){
        Types *y = pop(s);

		conv_float(y);
		push(s, y);
		return 1;

	} else return 0;
}

/**
 * Converte o elemento no topo da stack para string
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int toString(Stack *s, char *token){
    if(strcmp("s", token)==0){
        Types *y = pop(s);

		conv_string(y);
		push(s, y);
		return 1;

	} else return 0;
}

/**
 * Converte o elemento no topo da stack para char
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int toChar(Stack *s, char *token){
    if(strcmp("c", token)==0){
        Types *y = pop(s);

		conv_char(y);
		push(s, y);
		return 1;

	} else return 0;
}

/**
 * Imprime o elemento no topo da stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int print_top (Stack *s, char *token){
    if(strcmp("p", token)==0){
        Types *y = pop(s);
		
		switch(y->type) {
			case number:
				printf ("%ld\n", y->number);
				break;

			case single:
				printf ("%c\n", y->single);
				break;

			case string:
				printf ("%s\n", y->string);
				break;

			case floats:
				printf ("%f\n", y->floats);
				break;

			default:
				break;
			push(s, y);
		}
		return 1;

	} else return 0;
}

/**
 * Esta função adiciona os números inteiros à stack quando recebe uma string
 * @param s A stack
 * @param token A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int stackAdderInt(Stack *s, char *token){
    for (int i = 0; i < (int) strlen(token); i++) 
        if(!isdigit(token[i])) 
            return 0;
    int num = atoi(token);
    push(s, initNumber(num));
    return 1; 
}

/**
 * Esta função adiciona os números decimais à stack quando recebe uma string
 * @param s A stack
 * @param token A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int stackAdderFloat(Stack *s, char *token){
    double num = atof(token);
    if(num == 0.0 && strcmp("0.0", token))
        return 0;
    push(s, initFloat(num));
    return 1;
}

/**
 * Esta função adiciona os caracteres à stack quando recebe uma string
 * @param s A stack
 * @param token A string a converter
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int stackAdderChar(Stack *s, char *token){
    if(strlen(token)==1){
        push(s, initChar(token[0]));
        return 1;
    }
    else return 0;
}

/**
 * Esta função adiciona uma string à stack quando a recebe
 * @param s A stack
 * @param token A string a converter
 * 
 * @return Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int stackAdderString(Stack *s, char *token){
    if(strlen(token) >= 1) {
		push(s, initString(token));
        return 1;
    }
    else return 0;   
}

/**
 * Lê a próxima linha de input e acrescenta à stack
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int read_line (Stack *s, char *token){
	char line[10240];

    if(strcmp("l", token)==0){
		assert( fgets(line, 10240, stdin) != NULL);

		if (stackAdderChar(s,line) == 1) return 1;
		if (stackAdderFloat(s,line) == 1) return 1;
		if (stackAdderInt(s,line) == 1) return 1;
		if (stackAdderString(s,line) == 1) return 1;
		return 1;

	} else return 0;
}

/**
 * Lê todas as linhas de input e acrescenta à stack como strings
 * 
 * @param s Stack
 * @param token Caracter que ativa a função
 * @return Caso o token ative a função retorna 1, caso contrário retorna 0
 */
int read_all(Stack *s, char *token){
	char line[10240];

    if(strcmp("t", token)==0){
		assert( fgets(line, 10240, stdin) != NULL);

		while (line[0]!='\n') {
			stackAdderString(s,line);
			assert( fgets(line, 10240, stdin) != NULL);
		}
		return 1;

	} else return 0;
}

/**
 * Esta função cobre os casos de o input ser uma variável
 * 
 * @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int new_var(Stack *s, char *token){
	int x = (int)token[0] - 65;
	Types *y = s->var[x];

	if(token[0]==':'){
		s->var[(int)token[1] - 65] = s->values[(s->size - 1)];
		return 1;

	} else if ((y == NULL) && x>=0 && x<=25){ 
		if (x == 13){
			push(s, initChar('\n'));

		}else if (x == 18){
			push(s, initChar(' '));

		}else if ((x >= 0 && x <= 22) && x != 18 && x != 13){
			x +=10;
			push(s, initNumber(x));

		}else if ((x >= 23 && x <= 25) && x != 18 && x != 13){
			x -= 23;
			push(s, initNumber(x));

		} return 1;

	} else if (y != NULL) {
		push(s, y);
		return 1;
	}
	else return 0;
}

/**
 * Esta função aplica a função de igualdade aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma. Caso, o elemento no topo da stack seja um number (y) e o seguinte seja uma string/array, devolve elemento de indice (y) da string/array
 * 
 * @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int eq(Stack *s, char *token){
	if (strcmp (token, "=") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		if (y->type==number && x->type==string)
			push(s, initChar(x->string[y->number]));
		
		else {
			converte (maxt->type, mint);

			if (y->type == number)
				push(s, initNumber(y->number == x->number));
			else if (y->type == floats)
				push(s, initNumber(y->floats == x->floats));
			else if (y->type == single)
				push(s, initNumber(y->single == x->single));
			else if (y->type == string) {
				int flag = 0;
				if (strcmp(y->string, x->string) == 0) flag = 1;
				push(s, initNumber(flag));
			}
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de menor aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma. Caso, o elemento no topo da stack seja um number (y) e o seguinte seja uma string/array, devolve os primeiros (y) elementos da string/array
 * 
 * @param s A stack
 * @param token A string a converter
 * -
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int lesser(Stack *s, char *token){
	if (strcmp (token, "<") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		if (y->type==number && x->type==string) {
			char new[y->number];
			int i;
			for (i=0; i<y->number; i++) new[i] = x->string[i];
			new[i] = '\0';
			push(s, initString(new));
		}
		else {
			converte (maxt->type, mint);

			if (y->type == number)
				push(s, initNumber(y->number > x->number));
			else if (y->type == floats)
				push(s, initNumber(y->floats > x->floats));
			else if (y->type == single)
				push(s, initNumber(y->single > x->single));
			else if (y->type == string) {
				int flag = 0;
				if (strcmp(x->string, y->string) < 0) flag = 1;
				push(s, initNumber(flag));
			}
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de maior aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma. Caso, o elemento no topo da stack seja um number (y) e o seguinte seja uma string/array, devolve os ultimos (y) elementos da string/array
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int bigger(Stack *s, char *token){
	if (strcmp (token, ">") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		if(y->type==number && x->type==string) {
			x->string += ((int)strlen(x->string)-y->number);
			push(s, initString(x->string));
		}
		else {
			converte(maxt->type, mint);

			if (y->type == number)
				push(s, initNumber(x->number > y->number));
			else if (y->type == floats)
				push(s, initNumber(x->floats > y->floats));
			else if (y->type == single)
				push(s, initNumber(x->single > y->single));
			else if (y->type == string) {
				int flag = 0;
				if (strcmp(x->string, y->string) > 0) flag = 1;
				push(s, initNumber(flag));
			}
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de "not" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token A string a converter
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int not(Stack *s, char *token){
		if (strcmp (token, "!") == 0) {       
			Types *y = pop(s);

			if (y->type == number)
				push(s, initNumber(! y->number));
			else if (y->type == floats)
				push(s, initNumber(! y->floats));
			else if (y->type == single)
				push(s, initNumber(! y->single));

			return 1;

		} else return 0;
}

/**
 * Esta função aplica a função "and" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int and(Stack *s, char *token){
	if (strcmp (token, "e&") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number){
			if (x->number != '\0') push(s, y);
			else push(s, x);

		} else if (y->type == floats){
			if (x->floats != '\0') push(s, y);
			else push(s, x);

		} else if (y->type == single){
			if (x->single != '\0') push(s, y);
			else push(s, x);

		} else if (y->type == string){
			if (x->string != NULL) push(s, y);
			else push(s, x);
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função "or" aos dois últimos elementos da stack e, se conseguir, adiciona-o à mesma
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int or(Stack *s, char *token){
	if (strcmp (token, "e|") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number){
			if (x->number != '\0') push(s, x);
			else push(s, y);

		} else if (y->type == floats){
			if (x->floats != '\0') push(s, x);
			else push(s, y);

		} else if (y->type == single){
			if (x->single != '\0') push(s, x);
			else push(s, y);

		} else if (y->type == string){
			if (x->string != NULL) push(s, x);
			else push(s, y);
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de menor aos dois últimos elementos da stack e adiciona à stack o menor elemento
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int push_lesser(Stack *s, char *token){
	if (strcmp (token, "e<") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number){
			if (x->number < y->number) push(s, x);
			else push(s, y);

		}else if (y->type == floats) {
			if (x->floats < y->floats) push(s, x);
			else push(s, y);

		}
		else if (y->type == single){
			if (x->floats < y->floats) push(s, x);
			else push(s, y);

		} else if (y->type == string){
			if (strcmp(x->string, y->string) < 0) push(s, x);
			else push(s, y);
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de maior aos dois últimos elementos da stack e adiciona à stack o maior elemento
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int push_bigger(Stack *s, char *token){
	if (strcmp (token, "e>") == 0) {       
		Types *y = pop(s);
		Types *x = pop(s);
		Types *maxt = max_type(x, y);
		Types *mint = min_type(x, y);

		converte(maxt->type, mint);

		if (y->type == number){
			if (x->number > y->number) push(s, x);
			else push(s, y);

		} else if (y->type == floats) {
			if (x->floats > y->floats) push(s, x);
			else push(s, y);

		} else if (y->type == single){
			if (x->floats > y->floats) push(s, x);
			else push(s, y);

		} else if (y->type == string){
			if ((strcmp(x->string, y->string) > 0)) push(s, x);
			else push(s, y);
		}
		return 1;
	
	} else return 0;
}

/**
 * Esta função aplica a função de condição ao elementos da stack
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int if_then_else(Stack *s, char *token){
	if (strcmp (token, "?") == 0) {       
		Types* z = pop(s);
		Types* y = pop(s);
		Types* x = pop(s);
		Types *maxt = max_type(max_type(x, y), max_type(y,z));
		converte(maxt->type, x);
		converte(maxt->type, y);
		converte(maxt->type, z);
		

		if (x->type == number){
			if (x->number != '\0') push(s, y);
			else push(s,z);
			
		} else if (x->type == single){
			if (x->single != '\0') push(s,y);
			else push(s,z);

		} else if (x->type == floats){
			if (x->floats != '\0') push(s,y);
			else push(s,z);

		} return 1;
	} else return 0;
}

/**
 * Caso o elemento no topo da stack seja um number, devolve um array com o range de elementos do 0 até ao elemento no topo da stack, caso seja uma string devolve o seu tamanho
 * 
 * @param s A stack
 * @param token Caracter que ativa a função
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int range (Stack *s, char *token){
	if (strcmp (token, ",") == 0) {       
		Types *y = pop(s);

		if (y->type == number) {
			for (int n = 0; n < y->number; n++)
				push(s, initNumber(n));

		/*} else if (y->type == floats)
			push(s, initNumber(! y->floats));
		else if (y->type == single)
			push(s, initNumber(! y->single));
			*/
		} else if (y->type == string)
			push(s, initNumber(strlen(y->string)));

		return 1;

	} else return 0;
}

/**
 * Separa a string do topo da stack por um whitespace
 * 
 * @param s A Stack
 * @param token Caracter que ativa a função
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int white_space (Stack *s, char *token){
	if (strcmp (token, "S/") == 0) {
		Types *y = pop(s);
		y->string = strtok(y->string, " ");
		push(s, y);
		return 1;
	}
	else return 0;
}

/**
 * Separa a string do topo da stack por um newlines
 * 
 * @param s A Stack
 * @param token Caracter que ativa a função
 * 
 * @returns Se conseguir adicionar retorna 1, caso contrário retorna 0
 */
int newlines (Stack *s, char *token){
	if (strcmp (token, "N/") == 0) {
		Types *y = pop(s);
		y->string = strtok(y->string, "\n");
		push(s, y);
		return 1;
	}
	else return 0;
}

/**
 * Implementa as funções de cálculo, conversão e manipulação da stack
 * 
 * @param s Stack
 * @param token Caracter de ativação de funções
 * @return Se realizar uma operação retorna 1, caso contrário retorna 0
 */
int compute_stack(Stack *s, char *token){
    if(plus_ops(s,token) == 1) return 1;
    if(minus_ops(s,token) == 1) return 1;
	if(mult_ops(s,token) == 1) return 1;
	if(div_ops(s,token) == 1) return 1;
	if(mod_ops(s,token) == 1) return 1;
	if(inc_ops(s,token) == 1) return 1;
	if(dec_ops(s,token) == 1) return 1;
	if(pow_ops(s,token) == 1) return 1;
	if(and_ops(s,token) == 1) return 1;  
	if(or_ops(s,token) == 1) return 1; 
	if(xor_ops(s,token) == 1) return 1; 
	if(not_ops(s,token) == 1) return 1;
	if(double_ops(s,token) == 1) return 1; 
	if(pop_ops(s,token) == 1) return 1; 
	if(swap2_ops(s,token) == 1) return 1;
	if(swap3_ops(s,token) == 1) return 1; 
	if(copy_n_ops(s,token) == 1) return 1;
	if(eq(s,token) == 1) return 1;
	if(lesser(s,token) == 1) return 1;
	if(bigger(s,token) == 1) return 1;
	if(not(s,token) == 1) return 1;
	if(or(s,token) == 1) return 1;
	if(and(s,token) == 1) return 1; 
	if(range(s,token) == 1) return 1;
	if(white_space(s,token) == 1) return 1;
	if(push_lesser(s,token) == 1) return 1; 
	if(push_bigger(s,token) == 1) return 1; 
	if(if_then_else(s,token) == 1) return 1;
	if(new_var(s,token) == 1) return 1;
	if(toInt(s,token) == 1) return 1;
	if(toChar(s,token) == 1) return 1;
	if(toString(s,token) == 1) return 1;
	if(toFloat(s,token) == 1) return 1;
	if(print_top(s,token) == 1) return 1;
	if(read_line(s,token) == 1) return 1;
	if(read_all(s,token) == 1) return 1;
	if(stackAdderInt(s,token) == 1) return 1;
    if(stackAdderFloat(s,token) == 1) return 1;
    if(stackAdderChar(s,token) == 1) return 1;
	if(stackAdderString(s,token) == 1) return 1;
    else return 0;
}
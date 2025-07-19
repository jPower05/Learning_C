#include <stdio.h>
#include <stdlib.h> /* for atof */
#include "calc.h"

#define MAX_INPUT_LINE 1000    /* max length of input equation */

/* Input Buffer */
char input_line[MAX_INPUT_LINE];
int input_index = 0;

/* reverse polish notation calculator */
int main(){
	int token_type;
	double operand2; /* used to temp store the popped value */
	char token[MAX_TOKEN_SIZE];


	while (read_line(input_line, MAX_INPUT_LINE) != 0)
    {
        input_index = 0;
		while((token_type = get_next_token(token)) != EOF){
			switch(token_type){
				case TOKEN_NUMBER:
					push(atof(token));
					break;
				case '+':
					push(pop() + pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '-':
					operand2 = pop();
					push(pop() - operand2);
					break;
				case '/':
					operand2 = pop();
					if(operand2 != 0.0){ /* checking for division by zero */
						push(pop() / operand2);
					}else
						printf("error, division by zero");
					break;
				case '\n':
					printf("\t%.8g\n", pop());	/* final result */
					break;
				default:
					printf("error, invalid operand encountered");
					break;
			}
		}
	}
	return 0;
}
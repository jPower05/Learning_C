#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <ctype.h>  // for isdigit()

#define MAXOPMAX_TOKEN_SIZE 100	/* max size of operand/operator */
#define MAX_STACK_SIZE 100	/* max size of the stack */
#define TOKEN_NUMBER '0'	/* signal that a number was found */
#define MAX_INPUT_LINE 1000    /* max length of input equation */

/* Stack */
int stack_position = 0;	/* next free stack position */
double value_stack[MAX_STACK_SIZE]; /* stack */

/* Input Buffer */
char input_line[MAX_INPUT_LINE];
int input_index = 0;

/* Function Declarations*/
int read_line(char line[], int max_length);
int get_next_token(char token[]);
void push(double);
double pop(void);

/* reverse polish notation calculator */
int main(){
	int token_type;
	double operand2; /* used to temp store the popped value */
	char token[MAXOPMAX_TOKEN_SIZE];


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

/* push : push f onto the stack */
void push(double value){
	if(stack_position < MAX_STACK_SIZE){
		value_stack[stack_position++] = value;
	}else{
		printf("error, stack full, can't push -> %g\n", value);
	}
}

/* pop : pop and return the top value from the stack */
double pop(void){
	if(stack_position > 0){
		return value_stack[--stack_position];	/* decrement before, to get the top of stack */
	}else{
		printf("error, empty stack \n");
		return 0.0;
	}
}


/* uses input_index to iterate through the char line[] */
int get_next_token(char token[]) {
	int token_index = 0;
   	int current_char;

	// End of line reached
    if ((current_char = input_line[input_index]) == '\0') {
        return EOF;
    }

   	// Skip spaces and tabs
    while (current_char == ' ' || current_char == '\t'){
        current_char = input_line[++input_index];
	}

    // Handle newline
    if (current_char == '\n') {
        input_index++;
        return '\n';
    }

	token[token_index++] = current_char;
	input_index++;

	// If the character is not a digit and not a decimal point, return it
	if (!isdigit(current_char) && current_char != '.'){
			token[token_index] = '\0';	// mark as end of the token array
			return current_char;  // it's not part of a number
	}
		

	// Collect integer part
    while (isdigit(input_line[input_index])){
        token[token_index] = input_line[input_index];
		token_index++;
		input_index++;
	}

	// Collect fraction part
    if (input_line[input_index] == '.') {
        token[token_index++] = input_line[input_index++];
        while (isdigit(input_line[input_index])){
            token[token_index++] = input_line[input_index++];
		}
    }

	token[token_index] = '\0';     // null-terminate the string

	return TOKEN_NUMBER;   // indicate that a number was found
}


/* read_line:  get line into s, return length */
int read_line(char line[], int max_length){
    int current_char;
	int index = 0;

    while (--max_length > 0 && (current_char = getchar()) != EOF && current_char != '\n')
        line[index++] = current_char;
    if (current_char == '\n')
        line[index++] = current_char;
    line[index] = '\0';
    return index;
}


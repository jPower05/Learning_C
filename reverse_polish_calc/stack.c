#include <stdio.h>
#include "calc.h"

#define MAX_STACK_SIZE 100	/* max size of the stack */

/* Stack */
int stack_position = 0;	/* next free stack position */
double value_stack[MAX_STACK_SIZE]; /* stack */

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
#include <stdio.h>
#include "calc.h"
#include <ctype.h>


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
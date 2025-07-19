#include <stdio.h>
#include "calc.h"

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
#include <stdio.h>
#include "sort_lines_alphabetic.h"

/* writelines: write the output lines in order*/
void writelines(char *lineptr[], int nlines){
    printf("writelines, nlines = %d\n", nlines);
    int i;
    for(int i = 0; i < nlines; i++){
        printf("printing\n");
        printf("%s\n", lineptr[i]);
    }
}
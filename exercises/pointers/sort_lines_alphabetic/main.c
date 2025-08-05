#include <stdio.h>
#include "sort_lines_alphabetic.h"

#define MAXLINES 5000
char *lineptr[MAXLINES];

int main(){
    int nlines;
    if((nlines = readlines(lineptr, MAXLINES)) >= 0){
        printf("done reading input\n");
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }else{
        printf("error: input too big to sort");
        return 1;
    }

}
 
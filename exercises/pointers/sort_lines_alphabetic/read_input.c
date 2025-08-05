#include <stdio.h>
#include <string.h>
#include "sort_lines_alphabetic.h"

#define MAXLEN 1000   /* max length of any input line*/

int get_line(char *buffer, int limit);
char *alloc(int n);

int readlines(char *lineptr[], int maxlines){
    int len;    /* length of current line*/
    int nlines; /* number of lines read*/
    char *p;    /* pointer to a char*/
    char line[MAXLEN];  /* char array of size MAXLEN*/

    printf("readlines\n");

    nlines = 0;
    while((len = get_line(line,MAXLEN)) > 0){
        /* the pointer p points to a newly allocated block of memory (inside buffer allocbuff[]), */
        if(nlines >= maxlines || (p = alloc(len)) == NULL){     
            return -1;
        }else{
            printf("store the line\n");
            line[len-1] = '\0'; /* delete newline character*/
            strcpy(p,line);     /* copy line to allocated memory*/
            lineptr[nlines++] = p;  /* store pointer in the array*/
        }
    }
    printf("nlines = %d\n",nlines);
    return nlines;
}

int get_line(char *buffer, int limit) {
    printf("getline\n");
    int ch;
    int i = 0;

    while (i < limit - 1 && (ch = getchar()) != EOF && ch != '\n') {
        buffer[i++] = ch;
    }
    if(ch == EOF){
        printf("reached EOF\n");
    }
    if (ch == '\n') {
        printf("new line\n");
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    printf("line len = %d\n", i);
    return i;
}

#define ALLOCSIZE 10000 /* size of available space*/
static char allocbuff[ALLOCSIZE];   /* storage for alloc*/
static char *alloc_ptr = allocbuff; /* next free position*/

/* check if we have enough space for new input, return a pointer to the start position of the string*/
char *alloc(int n){
    printf("alloc\n");
    if(allocbuff + ALLOCSIZE - alloc_ptr >= n){
        alloc_ptr += n;
        return alloc_ptr -n; /* old pointer position, start of the string*/
    }else{
        return 0;
    }
}
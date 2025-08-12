#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(void *x, void *y);
int subtract(void *x, void *y);

int operator(void *x, void *y, int (*func)(void *x, void *y));


int main(int arc, char*argv[]){

    // atoi converts input to a number
    char *op = argv[1]; // operation choice
    int x = atoi(argv[2]);      // first number
    int y = atoi(argv[3]);      // second number

    // Choose function pointer using ternary
    // point at address of add/subract function
    int (*func_ptr)(void *, void *) = (strcmp(op, "+") == 0) ? &add : &subtract;

    int res = operator(&x, &y, func_ptr);
    printf("x:%d y:%d = %d\n",x,y,res);
    return 0;
}

int add(void *x, void *y){
    return *(int *)x + *(int *)y;
}

int subtract(void *x, void *y){
    return *(int *)x - *(int *)y;
}

int operator(void *x, void *y, int (*func)(void *x, void *y)){
    return func(x,y);
}
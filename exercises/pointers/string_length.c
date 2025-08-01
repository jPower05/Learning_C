#include <stdio.h>

int len(char *s);

int main(){
    char str[] = "string";
    /* we can used &str[0] to point to the address of the first array element */
    /* could also use 'str' which points to the address of the start of the array */
    printf("string -> %s is %d characters long\n" , str, len(&str[0]));
}

int len(char *s){   /* function takes in a pointer to a memory address of a character*/
    char *p = s;    /* dereference to get the actual value of the character*/
    while(*p != '\0'){
        p++;        /* increment the pointer address using the while loop*/
    }
    return p - s;   /* return the difference between the array start point and the end point of the pointer */
}
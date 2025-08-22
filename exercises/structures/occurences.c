// demonstrating arrays of structures

// defining the struct each array element will contain
#include <stdio.h>
struct key{
    char *word;
    int count;
};

// external initialization of a struct array
struct key_const{
    char *word;
    int count;
} keytabs_const[] = {
    "auto",0,
    "break", 0,
    "case", 0,
    "char",0,
    "const", 0,
    "continue",0,
    "default",10,
    "unsigned",0,
    "void",0,
    "volatile",0,
    "while",0
};


int main(){
    int NKEYS = 10;
    // instanciating the array of key struct
    struct key keytabs[NKEYS];
    printf("%s count = %d\n", keytabs_const[6].word, keytabs_const[6].count);

}
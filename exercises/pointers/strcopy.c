#include <stdio.h>

void strcopy_arr(char *s, char *t);
void strcopy_ptr(char *s, char *t);

int main(){
    char s[] = "string";
    char t[] = "record";

    strcopy_arr(s,t);
    printf("s: %s, t: %s\n", s,t);

    strcopy_ptr(s,t);
    printf("s: %s, t: %s\n", s,t);
    return 0;
}

/*  copy t to s using array indexes */
void strcopy_arr(char *s, char *t){
    int i;
    i = 0;
    while((s[i] = t[i]) != '\0'){
        i++;
    }
}

/* copy t to s using pointers*/
void strcopy_ptr(char *s, char *t){
    while((*s++ = *t++) != '\0'){
        ;
    }
}
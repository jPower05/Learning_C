#include <stdio.h>

#define ALLOCSIZE 10000

char *alloc(int);
void afree(char *p);

static char allocbuffer[ALLOCSIZE];
static char *pAlloc = allocbuffer;



int main(){
    /* (the void *) is used to safely print a pointer value with the %p format specifier.   */
    char *p1 = alloc(100);
    printf("Allocated 100 bytes at: %p\n", (void*)p1);
    printf("Remaining space: %ld bytes\n", allocbuffer + ALLOCSIZE - pAlloc);

    char *p2 = alloc(200);
    printf("Allocated 200 bytes at: %p\n", (void*)p2);
    printf("Remaining space: %ld bytes\n", allocbuffer + ALLOCSIZE - pAlloc);

    afree(p1);  // Free back to p1
    printf("Freed back to: %p\n", (void*)p1);
    printf("Remaining space: %ld bytes\n", allocbuffer + ALLOCSIZE - pAlloc);

    char *p3 = alloc(50);
    printf("Allocated 50 bytes at: %p\n", (void*)p3);
    printf("Remaining space: %ld bytes\n", allocbuffer + ALLOCSIZE - pAlloc);

    return 0;
}

char *alloc(int n){
    /* check if we have enough space left*/
    if(allocbuffer + ALLOCSIZE - pAlloc >= n){
        pAlloc += n;
        return pAlloc - n;
    }else{
        return 0;
    }
}

void afree(char *p){
    if(p >= allocbuffer && p < allocbuffer + ALLOCSIZE){
        pAlloc = p;
    }
}
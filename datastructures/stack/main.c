#include "stack.h"
#include <time.h>    // for time()


typedef struct _stack_entry{
    int value;
}stack_entry;

int main(){
    srand(time(NULL));  // Seed the random number generator
    // create a stack
    stack *stack = stack_create(10);


    // Push some entries
    for (int i = 0; i < 10; ++i) {
        int r = rand() % 50;
        stack_entry *e = malloc(sizeof(stack_entry));
        e->value = r;
        if (!stack_push(stack, e)) {
            printf("Stack full. Couldn't push %d\n", r);
            free(e);
        }else{
            printf("pushed, %d\n", r);
        }
    }

    stack_entry *peeked = stack_peek(stack);
    if (peeked) {
        printf("Top of stack: %d\n", peeked->value);
    }

    // Pop all entries
    while (!stack_empty(stack)) {
        stack_entry *e = stack_pop(stack);
        printf("Popped: %d\n", e->value);
        free(e); // free popped entries!
    }

    // Clean up stack
    stack_destroy(stack);
    return 0;
}
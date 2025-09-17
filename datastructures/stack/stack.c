#include "stack.h"

struct _entry {
    void *object;
};

// ----- Stack definition -----

struct _stack{
    size_t capacity;   // Maximum number of entries
    size_t top;        // Index of the next empty slot (also current size)
    entry **items;     // Array of entry pointers
};

stack *stack_create(size_t capacity){
    //assign heap space
    stack *st = malloc(sizeof(*st));
    st->capacity = capacity;
    st->top = 0;
    st->items = malloc(capacity * sizeof(entry *));
    if (!st->items) {
        free(st);
        return NULL;
    }

    return st;
}


void stack_destroy(stack *stack){
    if(!stack) return;

    for(size_t i = 0; i < stack->top; i++){
        // free the entry
        free(stack->items[i]);
    }
    free(stack->items);
    free(stack);
}

bool stack_push(stack *stack, void *object){
    if(stack_full(stack)) return false;
    // have space on stack
    entry *e = malloc(sizeof(entry));
    e->object = object;

    stack->items[stack->top++] = e;    // post increment
    return true;
}

void *stack_pop(stack *stack){
    if(stack_empty(stack)) return NULL;
    // free the entry
    entry *current = stack->items[--stack->top];
    void *obj = current->object;
    free(current);
    // return the value
    return obj;
}

void *stack_peek(stack *stack){
    if(stack_empty(stack)) return NULL;
    entry *current = stack->items[stack->top - 1];
    if (!current) {
        printf("stack_peek: NULL entry at top - 1\n");
        return NULL;
    }
    return current->object;
}
bool stack_full(stack *stack){
    return stack->top == stack->capacity;
}
bool stack_empty(stack *stack){
    return stack->top == 0;
}

size_t stack_size(const stack *stack) {
    return stack->top;
}

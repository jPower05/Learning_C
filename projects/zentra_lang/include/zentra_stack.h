#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct ZentraStack {
    size_t count;      // number of elements currently on the stack
    size_t capacity;   // total allocated slots
    void **elements;   // array of void* pointers (can hold any pointer)
} zentra_stack_t;

// Creates a new stack with initial capacity
zentra_stack_t *new_zentra_stack(size_t capacity);

// Pushes a pointer onto the stack
bool push_zentra_stack(zentra_stack_t *stack, void *element);

// Pops a pointer off the stack
void *pop_zentra_stack(zentra_stack_t *stack);

// Returns the element at the top without removing it
void *peek_zentra_stack(zentra_stack_t *stack);

// Frees the stack (does not free the elements themselves)
void free_zentra_stack(zentra_stack_t *stack);

void remove_nulls_from_zentra_stack(zentra_stack_t *stack);

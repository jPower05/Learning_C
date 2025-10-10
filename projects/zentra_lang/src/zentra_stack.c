#include "../include/zentra_stack.h"
#include <string.h>

zentra_stack_t *new_zentra_stack(size_t capacity) {
    if (capacity == 0) capacity = 8;

    zentra_stack_t *stack = malloc(sizeof(zentra_stack_t));
    if (!stack) return NULL;

    stack->elements = calloc(capacity, sizeof(void *));
    if (!stack->elements) {
        free(stack);
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capacity;
    return stack;
}

bool push_zentra_stack(zentra_stack_t *stack, void *element) {
    if (!stack) return false;

    // grow if necessary
    if (stack->count >= stack->capacity) {
        size_t new_capacity = stack->capacity * 2;
        void **new_elements = realloc(stack->elements, new_capacity * sizeof(void *));
        if (!new_elements) return false;

        stack->elements = new_elements;
        stack->capacity = new_capacity;
    }

    stack->elements[stack->count] = element;
    stack->count++;
    return true;
}

void *pop_zentra_stack(zentra_stack_t *stack){
    if (!stack || stack->count == 0) return NULL;
    stack->count--;
    return stack->elements[stack->count];
}

void *peek_zentra_stack(zentra_stack_t *stack){
    if (!stack || stack->count == 0) return NULL;
    return stack->elements[stack->count - 1];
}

void free_zentra_stack(zentra_stack_t *stack){
    if (!stack) return;
    if(stack->elements){
        free(stack->elements);
    }
    
    free(stack);
}

void remove_nulls_from_zentra_stack(zentra_stack_t *stack){
    if (!stack || stack->count == 0) {
        return; // nothing to do
    }

    size_t next_valid_index = 0;

    // Compact all non-NULL elements toward the start of the stack
    for (size_t i = 0; i < stack->count; i++) {
        void *element = stack->elements[i];
        if (element != NULL) {
            stack->elements[next_valid_index++] = element;
        }
    }

    // Clear any remaining (now-unused) slots
    for (size_t i = next_valid_index; i < stack->capacity; i++) {
        stack->elements[i] = NULL;
    }

    // Update the count to reflect the new number of valid elements
    stack->count = next_valid_index;
}

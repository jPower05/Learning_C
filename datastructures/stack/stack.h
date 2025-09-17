#pragma once
#include <stdbool.h>  // for bool
#include <stddef.h>   // for size_t
#include <stdlib.h>  // for rand() and srand()
#include <stdio.h>

typedef struct _stack stack;
typedef struct _entry entry;

stack *stack_create(size_t capacity);
void stack_destroy(stack *stack);
bool stack_push(stack *stack, void *object);
void *stack_pop(stack *stack);
void *stack_peek(stack *stack);
bool stack_full(stack *stack);
bool stack_empty(stack *stack);
size_t stack_size(const stack *stack);
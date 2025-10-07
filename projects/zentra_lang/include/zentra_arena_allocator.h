#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *base;
    size_t size;
    size_t used;
} zentra_arena_t;

zentra_arena_t *zentra_arena_create(size_t size);
void *zentra_arena_alloc(zentra_arena_t *arena, size_t bytes);
void zentra_arena_reset(zentra_arena_t *arena);
void zentra_arena_destroy(zentra_arena_t *arena);